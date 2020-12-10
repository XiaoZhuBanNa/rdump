#include <iostream>
#include "llvm/Support/CommandLine.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/BinaryFormat/Magic.h"
#include "llvm/Support/raw_ostream.h"
#include "ObjFile.h"
#include "Memory.h"

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

static File *addFile(StringRef path) {
  Optional<MemoryBufferRef> buffer = readFile(Library);
  if (!buffer)
    return nullptr;
  MemoryBufferRef mbref = *buffer;
  File *newFile = nullptr;
  
  switch (identify_magic(mbref.getBuffer())) {
    case file_magic::archive: {
      break;
    }
    case file_magic::macho_object:
      newFile = make<ObjFile>(mbref, "");
      break;
    case file_magic::macho_dynamically_linked_shared_lib:
    case file_magic::macho_dynamically_linked_shared_lib_stub:
      break;
    case file_magic::macho_bundle:
      break;
    case file_magic::tapi_file:
      break;
    default:
      errs() << Library + ": unhandled file type" << "\n";
  }
  
  return newFile;
}

int main(int argc, char *argv[]) {
  cl::ParseCommandLineOptions(argc, argv);
  
  addFile(Library);
  
  
  
  // llvm::for_each(InputFilenames, dumpInput);
  
  return EXIT_SUCCESS;
}
