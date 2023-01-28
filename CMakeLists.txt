cmake_minimum_required(VERSION 3.25)
project(ColorVisionSimulation
  VERSION 0.0.0
)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCL REQUIRED)
find_package(OpenMP REQUIRED)
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

set(LUA_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/vendor/lua/include CACHE PATH "Lua 5.1.4")
set(LUA_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/vendor/lua CACHE PATH "Lua 5.1.4")

add_subdirectory(lib)
add_subdirectory(script)
add_subdirectory(test)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-8 /execution-charset:shift_jis>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8 /execution-charset:shift_jis>")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/bin/aviutl)
install(TARGETS libcvs RUNTIME DESTINATION script)
install(FILES ${SCRIPT_OUTPUT_FILES} DESTINATION script)
