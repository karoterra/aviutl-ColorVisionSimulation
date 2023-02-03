#include <format>
#include <lua.hpp>

#include "cl_manager.h"
#include "color.h"
#include "cvs_cl.h"
#include "cvs_cpu.h"
#include "cvs_params.h"
#include "macro.h"
#include "util.h"

// data, w, h = simulate(type, severity, data, w, h)
int Simulate(lua_State *L) {
  const int argc = lua_gettop(L);
  if (argc < 5) {
    return 0;
  }

  const auto type = cvs::ToColorVisionType(lua_tointeger(L, 1));
  const float severity = lua_tonumber(L, 2);
  auto image = reinterpret_cast<cvs::BGRA *>(lua_touserdata(L, 3));
  const int w = lua_tointeger(L, 4);
  const int h = lua_tointeger(L, 5);

  if (cvs::CLManager::GetInstance().IsAvailable()) {
    cvs::SimulateCL(type, severity, image, w * h);
  } else {
    cvs::SimulateCPU(type, severity, image, w * h);
  }

  return 3;
}

static const luaL_Reg functions[] = {
    {"simulate", Simulate},
    {nullptr, nullptr},
};

extern "C" __declspec(dllexport) int LUA_OPEN(LIB_NAME)(lua_State *L) {
  luaL_register(L, STRING(LIB_NAME), functions);

  lua_pushliteral(L, LIB_VERSION);
  lua_setfield(L, -2, "_VERSION");
  return 1;
}
