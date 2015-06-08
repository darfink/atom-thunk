#include <atom-thunk/ThisThunk.hpp>
#include <cassert>

namespace atom {
  void ThisThunk::GenerateThunk(std::vector<unsigned char>& thunk) {
    switch(mConvention) {
    case CallingConvention::Stdcall:
      thunk << static_cast<unsigned short>(0x0D8D)  /* lea ecx */
            << mContext                             /* this */
            << static_cast<unsigned char>(0xB8)     /* mov eax */
            << mMethod                              /* destination */
            << static_cast<unsigned short>(0xE0FF); /* jmp eax */
      break;
    default: assert(false);
    }
  }
}
