add_executable(test_cvs test_cvs.cpp test_kernel.cpp)
target_include_directories(test_cvs PRIVATE ${STB_INCLUDE_DIRS})
target_link_libraries(test_cvs
  PRIVATE
    GTest::gtest GTest::gtest_main
    libcvs
    OpenCL::OpenCL
)

gtest_add_tests(TARGET test_cvs WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
