#ifndef CVS_LIB_CL_MANAGER_H_
#define CVS_LIB_CL_MANAGER_H_

#include <memory>

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

namespace cvs {

class CLManager {
 private:
  CLManager();
  ~CLManager() = default;

 public:
  CLManager(const CLManager&) = delete;
  CLManager& operator=(const CLManager&) = delete;
  CLManager(CLManager&&) = delete;
  CLManager& operator=(CLManager&&) = delete;

  static CLManager& GetInstance();

  bool IsAvailable() const noexcept { return is_available_; }

  cl::Context& GetContext() const { return *context_; }
  cl::CommandQueue& GetCommandQueue() const { return *queue_; }
  cl::Program& GetProgram() const { return *program_; }

 private:
  bool is_available_;
  std::unique_ptr<cl::Context> context_;
  std::unique_ptr<cl::CommandQueue> queue_;
  std::unique_ptr<cl::Program> program_;
};

}  // namespace cvs

#endif  // CVS_LIB_CL_MANAGER_H_
