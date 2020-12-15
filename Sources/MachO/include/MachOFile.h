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
  static bool classof(const File *f) { return f->kind() == ObjKind; }
    
  const MachO::mach_header &getHeader() const;
  
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
  
  void test();
  
  void parseLoadCommands();
  void parseSections();
  
private:
  MachO::mach_header_64 header;
  SmallVector<std::unique_ptr<MachO::load_command>, 4> loadCommands;
  SmallVector<std::unique_ptr<MachO::section_64>, 8> sectionHeaders;
//  ArrayRef<MachO::section_64> sectionHeaders;
  ArrayRef<MachO::segment_command_64> segments;
  ArrayRef<MachO::nlist_64> symbols;
  char *strtab;
  
  MachO::uuid_command uuidLoadCmd;
  MachO::symtab_command symtabLoadCmd;
  MachO::dysymtab_command dysymtabLoadCmd;
  
  void parseDebugInfo();
};

}

#endif
