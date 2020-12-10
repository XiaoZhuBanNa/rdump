#ifndef File_h
#define File_h

#include <stdio.h>
#include "llvm/Support/MemoryBuffer.h"

using namespace llvm;

namespace macho {

class File {
public:
  enum Kind {
    ObjKind,
    OpaqueKind,
    DylibKind,
    ArchiveKind,
    BitcodeKind,
  };
  
  virtual ~File() = default;
  Kind kind() const { return fileKind; }
  
  MemoryBufferRef mb;
  
protected:
  File(Kind kind, MemoryBufferRef mb)
      : mb(mb), fileKind(kind), name(mb.getBufferIdentifier()) {}
  
private:
  const Kind fileKind;
  const StringRef name;
};

}

#endif /* File_h */
