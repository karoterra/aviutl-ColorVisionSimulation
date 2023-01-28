add_library(libcvs SHARED)
target_sources(libcvs
  PUBLIC
    cl_manager.h
    cvs_params.h
    cvs_cl.h
    cvs_cpu.h
    color.h
    macro.h
    util.h
    cl_manager.cpp
    cvs_params.cpp
    cvs_cl.cpp
    cvs_cpu.cpp
    util.cpp
  PRIVATE
    main.cpp
    kernel.cl
)
target_include_directories(libcvs
  PUBLIC
    ${LUA_INCLUDE_DIR}
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_directories(libcvs PRIVATE ${LUA_LIBRARY_DIR})
target_link_libraries(libcvs
  PUBLIC
    OpenCL::OpenCL
    OpenMP::OpenMP_CXX
    delayimp.lib
  PRIVATE
    lua51
)
target_compile_definitions(libcvs
  PRIVATE
    LIB_NAME=KaroterraColorVisionSimulation
    LIB_VERSION="${PROJECT_VERSION}"
)
set_target_properties(libcvs PROPERTIES
  OUTPUT_NAME KaroterraColorVisionSimulation
)
target_link_options(libcvs PUBLIC "$<$<C_COMPILER_ID:MSVC>:/DELAYLOAD:OpenCL.dll>")
target_link_options(libcvs PUBLIC "$<$<CXX_COMPILER_ID:MSVC>:/DELAYLOAD:OpenCL.dll>")
