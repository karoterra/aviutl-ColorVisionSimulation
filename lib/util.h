#ifndef CVS_LIB_UTIL_H_
#define CVS_LIB_UTIL_H_

#include <string>

namespace cvs {

int CheckDelayException(int code);
bool IsDllAvailable(const char* name);

void DebugPrint(const std::string& s);

}  // namespace cvs

#endif  // CVS_LIB_UTIL_H_
