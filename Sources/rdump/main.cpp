#include <iostream>
#include "llvm/Support/CommandLine.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/BinaryFormat/Magic.h"
#include "llvm/Support/raw_ostream.h"
#include "MachOFile.h"
#include "FatFile.h"
#include "Memory.h"
#include "ArchiveFile.h"

using namespace llvm;
using namespace macho;

static cl::opt<std::string> Library("library",
                                    cl::Optional,
                                    cl::desc("library path"),
                                    cl::Optional);

static cl::list<std::string> InputFilenames(cl::Optional,
                                            cl::desc("<input object files>"),
                                            cl::ZeroOrMore,
                                            cl::Optional);

static cl::list<std::string> Arch("arch",
                                  cl::Optional,
                                  cl::desc("Target arch to disassemble for, "
                                           "see -version for available targets"),
                                  cl::ZeroOrMore,
                                  cl::Optional);

/// Open file and figure out how to dump it.
static void dumpInput(StringRef file) {
  
}

static File *processFile(StringRef path) {
  Optional<MemoryBufferRef> buffer = readFile(Library);
  
  if (!buffer)
    return nullptr;
  
  MemoryBufferRef mbref = *buffer;
  File *newFile = nullptr;
  
  switch (identify_magic(mbref.getBuffer())) {
    case file_magic::archive:
      newFile = make<ArchiveFile>(mbref);
      break;
    case file_magic::macho_universal_binary:
      newFile = make<FatFile>(mbref);
      break;
    case file_magic::macho_object:
    case file_magic::macho_executable:
    case file_magic::macho_fixed_virtual_memory_shared_lib:
    case file_magic::macho_core:
    case file_magic::macho_preload_executable:
    case file_magic::macho_dynamically_linked_shared_lib:
    case file_magic::macho_dynamic_linker:
    case file_magic::macho_bundle:
    case file_magic::macho_dynamically_linked_shared_lib_stub:
    case file_magic::macho_dsym_companion:
    case file_magic::macho_kext_bundle:
      newFile = make<MachOFile>(mbref, "");
      break;
      
    default:
      errs() << Library + ": unhandled file type" << "\n";
  }
  
  return newFile;
}

int main(int argc, char *argv[]) {
  cl::ParseCommandLineOptions(argc, argv);
  
  processFile(Library);
  
  // llvm::for_each(InputFilenames, dumpInput);
  
  return EXIT_SUCCESS;
}
