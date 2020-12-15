#include "MachOFile.h"
#include "Memory.h"
#include "llvm/Support/Endian.h"
#include "llvm/BinaryFormat/MachO.h"
#include <iostream>

using namespace llvm;
using namespace llvm::MachO;
using namespace llvm::support::endian;
using namespace macho;

bool MachOFile::is64Bit() const {
  return true;
}

MachOFile::MachOFile(MemoryBufferRef mb,StringRef archiveName) : File(ObjKind, mb) {
  auto *buf = reinterpret_cast<const uint8_t *>(mb.getBufferStart());
  auto *hdr = reinterpret_cast<const mach_header_64 *>(mb.getBufferStart());

  header = *hdr;
  auto *loadCmdAddress = reinterpret_cast<const uint8_t *>(hdr) + sizeof(mach_header_64);

  for (uint32_t i = 0; i < hdr->ncmds; ++i) {
    auto *cmd = reinterpret_cast<const load_command *>(loadCmdAddress);
    
    // push element to loadCommands
    loadCommands.push_back(std::make_unique<load_command>());
    loadCommands.back()->cmd = cmd->cmd;
    loadCommands.back()->cmdsize = cmd->cmdsize;
    
    switch (cmd->cmd) {
      // reference from dsdump
      case LC_LOAD_DYLIB:
      case LC_LOAD_WEAK_DYLIB:
      case LC_REEXPORT_DYLIB:
      case LC_LOAD_UPWARD_DYLIB: {
        // ...
        break;
      }
      case LC_BUILD_VERSION: {
        // ...
        break;
      }
      case LC_VERSION_MIN_IPHONEOS: {
        // ...
        break;
      }
      case LC_RPATH: {
        // ...
        break;
      }
      case LC_FUNCTION_STARTS: {
        // ...
        break;
      }
      case LC_SYMTAB: {
        // ...
        auto *c = reinterpret_cast<const symtab_command *>(cmd);
        break;
      }
      case LC_DYSYMTAB: {
        // ...
        break;
      }
      case LC_SEGMENT_64: {
        // ...
        auto *c = reinterpret_cast<const segment_command_64 *>(cmd);
        auto *secHdrAddr = reinterpret_cast<const uint8_t *>(c) + sizeof(segment_command_64);
        
        // read section headers
        for (int i = 0; i < c->nsects; i++) {
          section_64 * secHdr = const_cast<section_64 *>(reinterpret_cast<const section_64 *>(secHdrAddr));
          sectionHeaders.push_back(std::unique_ptr<section_64>(secHdr));
          std::cout << sectionHeaders.back()->segname << " " << sectionHeaders.back()->sectname << std::endl;
          secHdrAddr += sizeof(section_64);
        }
        parseSections();
        break;
      }
      case LC_UUID: {
        // ...
        break;
      }
      default:
        // ...
        break;
    }
    // advance to next command
    loadCmdAddress += cmd->cmdsize;
  }
}

void MachOFile::parseDebugInfo() {
  
}

void MachOFile::parseSections() {
  for (auto &sec : sectionHeaders) {
    std::cout << sec->segname << " " << sec->sectname << std::endl;
  }
}

void MachOFile::test() {
  for (auto &lc : loadCommands) {
    std::cout << lc->cmdsize << std::endl;
  }
}
