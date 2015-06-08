#pragma once

namespace atom {
  /* Describes the different x86 calling conventions */
  enum class CallingConvention {
    Stdcall,
    Fastcall,
    CDecl,
  };
}
