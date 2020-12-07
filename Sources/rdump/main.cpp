#include "llvm/Support/CommandLine.h"
#include "llvm/ADT/STLExtras.h"
#include "MachODump.h"

using namespace llvm;

static cl::opt<std::string> Library("library",
                                    cl::Optional,
                                    cl::desc("library path"),
                                    cl::Optional);

static cl::list<std::string> InputFilenames(cl::Optional,
                                            cl::desc("<input object files>"),
                                            cl::ZeroOrMore,
                                            cl::Optional);

/// Open file and figure out how to dump it.
static void dumpInput(StringRef file) {
  
}

int main(int argc, char *argv[]) {
  cl::ParseCommandLineOptions(argc, argv);
  
  llvm::for_each(InputFilenames, dumpInput);
  
  return EXIT_SUCCESS;
}
