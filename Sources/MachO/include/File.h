#ifndef File_h
#define File_h

#include <stdio.h>
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/BinaryFormat/MachO.h"

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
    FatFileKind,
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

llvm::Optional<MemoryBufferRef> readFile(StringRef path);

const llvm::MachO::load_command *
findCommand(const llvm::MachO::mach_header_64 *, uint32_t type);
}

#endif /* File_h */
