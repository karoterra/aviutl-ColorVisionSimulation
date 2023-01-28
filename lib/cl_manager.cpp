#include "cl_manager.h"

#include <string>
#include <vector>

#include "macro.h"
#include "util.h"

namespace cvs {

CLManager::CLManager()
    : is_available_(false),
      context_(nullptr),
      queue_(nullptr),
      program_(nullptr) {
  if (!IsDllAvailable("OpenCL.dll")) {
    is_available_ = false;
    DebugPrint("OpenCL.dll is not available.");
    return;
  }

  try {
    context_ = std::make_unique<cl::Context>(CL_DEVICE_TYPE_DEFAULT);
  } catch (cl::Error) {
    is_available_ = false;
    DebugPrint("OpenCL device is not found.");
    return;
  }

  try {
    queue_ = std::make_unique<cl::CommandQueue>(*context_);
  } catch (cl::Error) {
    is_available_ = false;
    DebugPrint("Failed to create OpenCL CommandQueue.");
    return;
  }

  const std::string kernel_source{
#include "kernel.cl"
  };
  try {
    program_ = std::make_unique<cl::Program>(*context_, kernel_source, true);
  } catch (cl::Error) {
    is_available_ = false;
    DebugPrint("Failed to build OpenCL kernel.");
    return;
  }

  is_available_ = true;
}

CLManager& CLManager::GetInstance() {
  static CLManager instance;
  return instance;
}

}  // namespace cvs
