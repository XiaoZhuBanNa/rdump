#ifndef ArchiveFile_h
#define ArchiveFile_h

#include <stdio.h>
#include "File.h"

namespace macho {

class ArchiveFile : public File {
public:
  explicit ArchiveFile(MemoryBufferRef mb);
  static bool classof(const File *f) { return f->kind() == ArchiveKind; }
  
};

}

#endif /* ArchiveFile_h */
