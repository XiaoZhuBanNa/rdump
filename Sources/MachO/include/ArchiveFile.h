#ifndef ArchiveFile_h
#define ArchiveFile_h

#include <stdio.h>
#include "File.h"

namespace macho {

class ArchiveFile : public File {
public:
  explicit ArchiveFile(MemoryBufferRef mb);
};

}

#endif /* ArchiveFile_h */
