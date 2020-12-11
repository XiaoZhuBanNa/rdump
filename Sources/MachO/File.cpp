#include "llvm/Support/Endian.h"
#include "llvm/BinaryFormat/MachO.h"

#include "File.h"
#include "Memory.h"

using namespace llvm;
using namespace llvm::MachO;
using namespace llvm::support::endian;

// Open a given file path and return it as a memory-mapped file.
Optional<MemoryBufferRef> macho::readFile(StringRef path) {
  // Open a file.
  auto mbOrErr = MemoryBuffer::getFile(path);
  if (auto ec = mbOrErr.getError()) {
    errs() << "cannot open " + path + ": " + ec.message() << "\n";
    return None;
  }

  std::unique_ptr<MemoryBuffer> &mb = *mbOrErr;
  MemoryBufferRef mbref = mb->getMemBufferRef();
  make<std::unique_ptr<MemoryBuffer>>(std::move(mb)); // take mb ownership
  
  return mbref;

//  // Object files and archive files may be fat files, which contains
//  // multiple real files for different CPU ISAs. Here, we search for a
//  // file that matches with the current link target and returns it as
//  // a MemoryBufferRef.
//  auto *arch = reinterpret_cast<const MachO::fat_arch *>(buf + sizeof(*hdr));
//
//  for (uint32_t i = 0, n = read32be(&hdr->nfat_arch); i < n; ++i) {
//    if (reinterpret_cast<const char *>(arch + i + 1) >
//        buf + mbref.getBufferSize()) {
//      errs() << path + ": fat_arch struct extends beyond end of file" << "\n";
//      return None;
//    }
//
//    uint32_t offset = read32be(&arch[i].offset);
//    uint32_t size = read32be(&arch[i].size);
//    if (offset + size > mbref.getBufferSize())
//      errs() << path + ": slice extends beyond end of file" << "\n";
//    return MemoryBufferRef(StringRef(buf + offset, size), path.copy(bAlloc));
//  }
}
