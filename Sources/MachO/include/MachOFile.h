#ifndef MachOObjectFile_h
#define MachOObjectFile_h

#include <stdio.h>
#include "llvm/BinaryFormat/MachO.h"
#include "llvm/Support/MemoryBuffer.h"
#include "File.h"

using namespace llvm;

namespace macho {

class MachOFile : public File {
public:
  explicit MachOFile(MemoryBufferRef mb, StringRef archiveName);
    
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
  
  void parseSections(ArrayRef<llvm::MachO::section_64>);
  
private:
  MachO::mach_header_64 header64;
  ArrayRef<llvm::MachO::section_64> sections_64;
  ArrayRef<llvm::MachO::segment_command_64> segments_64;
  
  const char *symtabLoadCmd = nullptr;
  const char *dysymtabLoadCmd = nullptr;
  const char *dataInCodeLoadCmd = nullptr;
  const char *linkOptHintsLoadCmd = nullptr;
  const char *dyldInfoLoadCmd = nullptr;
  const char *uuidLoadCmd = nullptr;
  
  void parseDebugInfo();
};

}

#endif
