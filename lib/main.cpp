#include <lua.hpp>

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

static const luaL_Reg functions[] = {
    {nullptr, nullptr},
};

extern "C" __declspec(dllexport) int LUA_OPEN(LIB_NAME)(lua_State *L) {
  luaL_register(L, STRING(LIB_NAME), functions);

  lua_pushliteral(L, LIB_VERSION);
  lua_setfield(L, -2, "_VERSION");
  return 1;
}
