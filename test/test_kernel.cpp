#include <gtest/gtest.h>

#include <CL/cl.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::string BuildStatusToString(cl_build_status status) {
  switch (status) {
    case CL_BUILD_NONE:
      return "None";
    case CL_BUILD_ERROR:
      return "Error";
    case CL_BUILD_SUCCESS:
      return "Success";
    case CL_BUILD_IN_PROGRESS:
      return "In Progress";
  }
  return "unknown";
}

std::string BuildResultToString(cl_int result) {
  switch (result) {
    case CL_SUCCESS:
      return "Success";
    case CL_INVALID_PROGRAM:
      return "Invalid program";
    case CL_INVALID_VALUE:
      return "Invalid value";
    case CL_INVALID_DEVICE:
      return "Invalid device";
    case CL_INVALID_BINARY:
      return "Invalid binary";
    case CL_INVALID_BUILD_OPTIONS:
      return "Invalid build options";
    case CL_INVALID_OPERATION:
      return "Invalid operation";
    case CL_COMPILER_NOT_AVAILABLE:
      return "Compiler not available";
    case CL_BUILD_PROGRAM_FAILURE:
      return "Build program failure";
    case CL_OUT_OF_RESOURCES:
      return "Out of resources";
    case CL_OUT_OF_HOST_MEMORY:
      return "Out of host memory";
  }
  return "unknown";
}

TEST(KernelTest, BuildKernel) {
  std::ifstream ifs("lib/kernel.cl");
  EXPECT_FALSE(ifs.fail());

  std::string source((std::istreambuf_iterator<char>(ifs)),
                     std::istreambuf_iterator<char>());

  cl::Context context(CL_DEVICE_TYPE_DEFAULT);
  std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();

  cl::Program program(context, source);
  auto result = program.build("-Werror");
  auto status = program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(devices[0]);

  fs::create_directories("test_out");
  std::ofstream ofs("test_out/build_kernel_result.txt");

  ofs << "Result: " << BuildResultToString(result) << std::endl;
  ofs << "Status: " << BuildStatusToString(status) << std::endl;
  ofs << "Options: "
      << program.getBuildInfo<CL_PROGRAM_BUILD_OPTIONS>(devices[0])
      << std::endl;
  ofs << "Log: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0])
      << std::endl;

  EXPECT_EQ(result, CL_SUCCESS);
  EXPECT_EQ(status, CL_BUILD_SUCCESS);
}
