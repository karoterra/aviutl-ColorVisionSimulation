#include "util.h"

#define NOMINMAX
#include <Windows.h>
#include <delayimp.h>

#include <format>

#include "macro.h"

namespace cvs {

int CheckDelayException(int code) {
  if (code == VcppException(ERROR_SEVERITY_ERROR, ERROR_MOD_NOT_FOUND) ||
      code == VcppException(ERROR_SEVERITY_ERROR, ERROR_PROC_NOT_FOUND)) {
    return EXCEPTION_EXECUTE_HANDLER;
  }
  return EXCEPTION_CONTINUE_SEARCH;
}

bool IsDllAvailable(const char* name) {
  __try {
    auto ret = __HrLoadAllImportsForDll(name);
    if (FAILED(ret)) return false;
  } __except (CheckDelayException(GetExceptionCode())) {
    return false;
  }
  return true;
}

void DebugPrint(const std::string& s) {
  OutputDebugStringA(std::format("[{}] {}", STRING(LIB_NAME), s).c_str());
}

}  // namespace cvs
