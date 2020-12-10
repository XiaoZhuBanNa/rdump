#include "Memory.h"

using namespace llvm;
using namespace macho;

BumpPtrAllocator macho::bAlloc;
StringSaver macho::saver{bAlloc};
std::vector<SpecificAllocBase *> macho::SpecificAllocBase::instances;

void macho::freeArena() {
  for (SpecificAllocBase *alloc : SpecificAllocBase::instances)
    alloc->reset();
  bAlloc.Reset();
}
