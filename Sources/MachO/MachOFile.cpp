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

MachOFile::MachOFile(MemoryBufferRef mb, StringRef archiveName) : File(ObjKind, mb) {
  auto *buf = reinterpret_cast<const uint8_t *>(mb.getBufferStart());
  auto *hdr = reinterpret_cast<const mach_header_64 *>(mb.getBufferStart());

  header = *hdr;
  
  uint32_t ncmds = hdr->ncmds;
  
  for (unsigned i = 0; i < ncmds; ++i) {
    auto *cmd = reinterpret_cast<const load_command *>(hdr);
    switch (cmd->cmd) {
      case LC_SEGMENT_64:
        
        break;
        
      default:
        break;
    }
  }
  
  if (const load_command *cmd = findCommand(hdr, LC_SEGMENT_64)) {
    auto *c = reinterpret_cast<const segment_command_64 *>(cmd);
    sectionHeaders = ArrayRef<section_64>{
        reinterpret_cast<const section_64 *>(c + 1), c->nsects};
  }
}

void MachOFile::parseDebugInfo() {
  
}
