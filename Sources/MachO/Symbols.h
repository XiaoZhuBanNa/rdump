#ifndef Symbols_h
#define Symbols_h

#include <stdio.h>
#include "llvm/ADT/StringRef.h"

using namespace llvm;

namespace macho {

class Symbol {
public:
  enum Kind {
    DefinedKind,
    UndefinedKind,
    CommonKind,
    DylibKind,
    LazyKind,
    DSOHandleKind,
  };
  
  virtual ~Symbol() = default;
  Symbol(Kind k, StringRef name) : symbolKind(k), name(name) {}
  
private:
  Kind symbolKind;
  StringRef name;
};
}

#endif /* Symbols_h */
