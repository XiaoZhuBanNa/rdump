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
  
  const MachO::mach_header &getHeader() const;
  const MachO::mach_header_64 &getHeader64() const;
  
  bool is64Bit() const;
};

llvm::Optional<MemoryBufferRef> readFile(StringRef path);

}

#endif
