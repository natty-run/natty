#ifndef GLFW_HPP
#define GLFW_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <string>

namespace glfw {

enum class Error {
  NotInitialized,
  NoCurrentContext,
  InvalidEnum,
  InvalidValue,
  OutOfMemory,
  APIUnavailable,
  VersionUnavailable,
  PlatformError,
  FormatUnavailable,
  NoWindowContext
};

class GlfwException : public std::runtime_error {
public:
  GlfwException(const char* message) : std::runtime_error(message) {}
  GlfwException(const std::string& message) : std::runtime_error(message) {}
};

inline void checkError() {
  const char* description;
  int code = glfwGetError(&description);

  if (code == GLFW_NO_ERROR) return;

  switch (code) {
    case GLFW_NOT_INITIALIZED:
      throw GlfwException("GLFW not initialized");
    case GLFW_NO_CURRENT_CONTEXT:
      throw GlfwException("No current context");
    case GLFW_INVALID_ENUM:
      throw GlfwException("Invalid enum");
    case GLFW_INVALID_VALUE:
      throw GlfwException("Invalid value");
    case GLFW_OUT_OF_MEMORY:
      throw GlfwException("Out of memory");
    case GLFW_API_UNAVAILABLE:
      throw GlfwException("API unavailable");
    case GLFW_VERSION_UNAVAILABLE:
      throw GlfwException("Version unavailable");
    case GLFW_PLATFORM_ERROR:
      throw GlfwException("Platform error");
    case GLFW_FORMAT_UNAVAILABLE:
      throw GlfwException("Format unavailable");
    case GLFW_NO_WINDOW_CONTEXT:
      throw GlfwException("No window context");
    default:
      throw GlfwException("Unknown GLFW error");
  }
}

}  // namespace glfw

#endif  // GLFW_HPP
