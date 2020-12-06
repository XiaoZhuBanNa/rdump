#ifndef MachOObjectFile_h
#define MachOObjectFile_h

#include <stdio.h>
#include "llvm/BinaryFormat/MachO.h"
#include "llvm/Support/MemoryBuffer.h"

using namespace llvm;

namespace macho {

class MachOObjectFile {
public:
  
  MemoryBufferRef mb;
  
  ~MachOObjectFile() = default;
  MachOObjectFile(MemoryBufferRef mb) : mb(mb) {}
};

llvm::Optional<MemoryBufferRef> readFile(StringRef path);

}

#endif
