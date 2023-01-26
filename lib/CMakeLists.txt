add_library(libcvs SHARED)
target_sources(libcvs
  PRIVATE
    main.cpp
)
target_include_directories(libcvs
  PUBLIC
    ${LUA_INCLUDE_DIR}
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_directories(libcvs PRIVATE ${LUA_LIBRARY_DIR})
target_link_libraries(libcvs
  PRIVATE
    lua51
    OpenCL::OpenCL
)
target_compile_definitions(libcvs
  PRIVATE
    LIB_NAME=KaroterraColorVisionSimulation
    LIB_VERSION="${PROJECT_VERSION}"
)
set_target_properties(libcvs PROPERTIES
  OUTPUT_NAME KaroterraColorVisionSimulation
)
