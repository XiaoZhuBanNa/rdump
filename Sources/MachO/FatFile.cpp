#include "FatFile.h"
#include "Memory.h"
#include "llvm/Support/Endian.h"
#include "llvm/BinaryFormat/MachO.h"

using namespace llvm;
using namespace llvm::MachO;
using namespace llvm::support::endian;
using namespace macho;

FatFile::FatFile(MemoryBufferRef mb, Error &Err) : File(ObjKind, mb) {
  
}

