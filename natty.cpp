#include <stdexcept>

#include "glfw.h"

int main() {
  try {
    if (glfwInit() != GLFW_TRUE) {
        throw std::runtime_error("GLFW initialization failed");
    }

    struct GlfwCleanup {
        ~GlfwCleanup() { glfwTerminate(); }
    } cleanup;

    return 0;
  }
  catch (const std::exception& e) {
    // Handle errors
    return 1;
  }
}
