cmake_minimum_required(VERSION 3.25)
project(ColorVisionSimulation
  VERSION 0.0.0
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCL REQUIRED)

set(LUA_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/vendor/lua/include CACHE PATH "Lua 5.1.4")
set(LUA_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/vendor/lua CACHE PATH "Lua 5.1.4")

add_subdirectory(lib)
add_subdirectory(script)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/bin/aviutl)
install(TARGETS libcvs RUNTIME DESTINATION script)
install(FILES ${SCRIPT_OUTPUT_FILES} DESTINATION script)
