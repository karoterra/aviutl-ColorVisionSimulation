#ifndef CVS_LIB_MACRO_H_
#define CVS_LIB_MACRO_H_

#ifndef LIB_NAME
#define LIB_NAME cvs
#endif

#ifndef LIB_VERSION
#define LIB_VERSION ""
#endif

#define LUA_OPEN(x) LUA_OPEN_(x)
#define LUA_OPEN_(x) luaopen_##x

#define STRING(x) STRING_(x)
#define STRING_(x) #x

#ifndef CL_KERNEL_SOURCE
#define CL_KERNEL_SOURCE(x) #x
#endif

#endif  // CVS_LIB_MACRO_H_
