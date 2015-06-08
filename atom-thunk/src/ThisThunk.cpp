#pragma once

#include <atom-memory/Memory.hpp>
#include <atom-thunk/ThisThunk.hpp>
#include <cassert>

namespace atom {
  ThisThunk::ThisThunk(void* method, void* context, CallingConvention cc) :
      mMethod(method),
      mContext(context),
      mConvention(cc) {
    assert(method != nullptr);
    assert(context != nullptr);

    std::vector<unsigned char> thunk;
    this->GenerateThunk(thunk);

    size_t allocated = 0;
    mMemory.reset(Memory::Allocate(thunk.size(), Memory::ReadWriteExecute, &allocated), [allocated](void* memory) {
      Memory::Free(memory, allocated);
    });

    std::memcpy(mMemory.get(), thunk.data(), thunk.size());
  }
}
