#ifndef FatFile_h
#define FatFile_h

#include <stdio.h>
#include "llvm/BinaryFormat/MachO.h"
#include "llvm/Support/MemoryBuffer.h"
#include "File.h"

using namespace llvm;

namespace macho {

class FatFile : public File {
public:
  explicit FatFile(MemoryBufferRef mb);
  
  uint32_t Magic;
  uint32_t NumberOfObjects;
  
public:
  static constexpr uint32_t MaxSectionAlignment = 15;
  
  class ObjectForArch {
    // ...
  };
  
  class object_iterator {
    // ...
  };
};

};

#endif /* FatFile_h */
