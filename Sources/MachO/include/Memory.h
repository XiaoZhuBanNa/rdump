#ifndef Header_h
#define Header_h

#include "llvm/Support/Allocator.h"
#include "llvm/Support/StringSaver.h"
#include <vector>

namespace macho {

// Use this arena if your object doesn't have a destructor.
extern llvm::BumpPtrAllocator bAlloc;
extern llvm::StringSaver saver;

void freeArena();

// These two classes are hack to keep track of all
// SpecificBumpPtrAllocator instances.
struct SpecificAllocBase {
  SpecificAllocBase() { instances.push_back(this); }
  virtual ~SpecificAllocBase() = default;
  virtual void reset() = 0;
  static std::vector<SpecificAllocBase *> instances;
};

template <class T> struct SpecificAlloc : public SpecificAllocBase {
  void reset() override { alloc.DestroyAll(); }
  llvm::SpecificBumpPtrAllocator<T> alloc;
};

// Use a static local for these singletons so they are only registered if an
// object of this instance is ever constructed. Otherwise we will create and
// register ELF allocators for COFF and the reverse.
template <typename T>
inline llvm::SpecificBumpPtrAllocator<T> &getSpecificAllocSingleton() {
  static SpecificAlloc<T> instance;
  return instance.alloc;
}

// Use this arena if your object has a destructor.
// Your destructor will be invoked from freeArena().
template <typename T, typename... U> T *make(U &&... args) {
  return new (getSpecificAllocSingleton<T>().Allocate())
      T(std::forward<U>(args)...);
}

} // namespace macho

#endif /* Header_h */
