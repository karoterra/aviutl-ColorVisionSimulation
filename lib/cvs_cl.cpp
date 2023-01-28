#include "cvs_cl.h"

#include <format>

#include "cl_manager.h"
#include "util.h"

namespace cvs {

void SimulateCL(ColorVisionType type, float severity, BGRA* image, size_t len) {
  switch (type) {
    case ColorVisionType::Protan:
    case ColorVisionType::Deutan:
      SimulateBrettel1997CL(type, severity, image, len);
      break;
    case ColorVisionType::Tritan:
      SimulateVienot1999CL(type, severity, image, len);
      break;
  }
}

void SimulateBrettel1997CL(ColorVisionType type, float severity, BGRA* image,
                           size_t len) {
  try {
    auto params = Brettel1997Params::Get(type);

    const auto& cl_manager = CLManager::GetInstance();
    const auto& context = cl_manager.GetContext();
    const auto& queue = cl_manager.GetCommandQueue();
    const size_t image_size = sizeof(BGRA) * len;
    constexpr size_t param_size = sizeof(*params);

    cl::Buffer buf_image(context, CL_MEM_READ_WRITE, image_size);
    cl::Buffer buf_params(context, CL_MEM_READ_ONLY, param_size);

    queue.enqueueWriteBuffer(buf_image, CL_TRUE, 0, image_size, image);
    queue.enqueueWriteBuffer(buf_params, CL_TRUE, 0, param_size, params);

    cl::Kernel kernel(cl_manager.GetProgram(), "Brettel1997");
    kernel.setArg(0, buf_image);
    kernel.setArg(1, buf_params);
    kernel.setArg(2, severity);

    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(len));
    queue.finish();

    queue.enqueueReadBuffer(buf_image, CL_TRUE, 0, image_size, image);
  } catch (const cl::Error& e) {
    DebugPrint("Failed to SimulateBrettel1997CL");
    DebugPrint(std::format("cl::Error({}, {})", e.err(), e.what()));
  }
}

void SimulateVienot1999CL(ColorVisionType type, float severity, BGRA* image,
                          size_t len) {
  try {
    auto params = Vienot1999Params::Get(type);

    const auto& cl_manager = CLManager::GetInstance();
    const auto& context = cl_manager.GetContext();
    const auto& queue = cl_manager.GetCommandQueue();
    const size_t image_size = sizeof(BGRA) * len;
    constexpr size_t param_size = sizeof(*params);

    cl::Buffer buf_image(context, CL_MEM_READ_WRITE, image_size);
    cl::Buffer buf_params(context, CL_MEM_READ_ONLY, param_size);

    queue.enqueueWriteBuffer(buf_image, CL_TRUE, 0, image_size, image);
    queue.enqueueWriteBuffer(buf_params, CL_TRUE, 0, param_size, params);

    cl::Kernel kernel(cl_manager.GetProgram(), "Vienot1999");
    kernel.setArg(0, buf_image);
    kernel.setArg(1, buf_params);
    kernel.setArg(2, severity);

    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(len));
    queue.finish();

    queue.enqueueReadBuffer(buf_image, CL_TRUE, 0, image_size, image);
  } catch (const cl::Error& e) {
    DebugPrint("Failed to SimulateVienot1999CL");
    DebugPrint(std::format("cl::Error({}, {})", e.err(), e.what()));
  }
}

}  // namespace cvs
