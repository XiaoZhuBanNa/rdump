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
  
  MachO::symtab_command getSymtabLoadCommand() const;
  MachO::dysymtab_command getDysymtabLoadCommand() const;
  MachO::linkedit_data_command getDataInCodeLoadCommand() const;
  MachO::linkedit_data_command getLinkOptHintsLoadCommand() const;
  ArrayRef<uint8_t> getDyldInfoRebaseOpcodes() const;
  ArrayRef<uint8_t> getDyldInfoBindOpcodes() const;
  ArrayRef<uint8_t> getDyldInfoWeakBindOpcodes() const;
  ArrayRef<uint8_t> getDyldInfoLazyBindOpcodes() const;
  ArrayRef<uint8_t> getDyldInfoExportsTrie() const;
  ArrayRef<uint8_t> getUuid() const;
  
  bool is64Bit() const;
  
private:
  const char *SymtabLoadCmd = nullptr;
  const char *DysymtabLoadCmd = nullptr;
  const char *DataInCodeLoadCmd = nullptr;
  const char *LinkOptHintsLoadCmd = nullptr;
  const char *DyldInfoLoadCmd = nullptr;
  const char *UuidLoadCmd = nullptr;
};

llvm::Optional<MemoryBufferRef> readFile(StringRef path);

}

#endif
