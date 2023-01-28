cmake_minimum_required(VERSION 3.25)
project(aviutl-ColorVisionSimulation)
set(PROJECT_VERSION 0.0.0-dev)

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

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/bin/aviutl/script/${PROJECT_NAME})
install(TARGETS libcvs RUNTIME DESTINATION .)
install(
  FILES
    ${SCRIPT_OUTPUT_FILES}
    README.md
    CHANGELOG.md
    CREDITS.md
    LICENSE
  DESTINATION .
)

add_custom_target(pack
  COMMAND
    ${CMAKE_COMMAND}
    -DMANIFEST_FILE="${CMAKE_BINARY_DIR}/install_manifest.txt"
    -DOUTPUT_FILE="publish/${PROJECT_NAME}_v${PROJECT_VERSION}.zip"
    -P pack.cmake
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  DEPENDS install
)
