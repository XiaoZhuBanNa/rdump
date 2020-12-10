#include "MachOFile.h"
#include "Memory.h"
#include "llvm/Support/Endian.h"
#include "llvm/BinaryFormat/MachO.h"

using namespace llvm;
using namespace llvm::MachO;
using namespace llvm::support::endian;
using namespace macho;

bool MachOFile::is64Bit() const {
  return true;
}

MachOFile::MachOFile(MemoryBufferRef mb,StringRef archiveName)
    : File(ObjKind, mb) {
      
}
