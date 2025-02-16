#include <iostream>
#include <memory>
#include <stdexcept>

#include "glfw.h"

struct GLFWwindowDeleter {
  void operator()(GLFWwindow* window) {
    glfwDestroyWindow(window);
  }
};

using GLFWwindowPtr = std::unique_ptr<GLFWwindow, GLFWwindowDeleter>;

int main() {
  try {
    if (glfwInit() != GLFW_TRUE) {
      throw glfw::GlfwException("Failed to initialize GLFW");
    }

    struct GLFWCleanup {
      ~GLFWCleanup() { glfwTerminate(); }
    } cleanup;

    GLFWwindowPtr window(glfwCreateWindow(640, 480, "My Title", nullptr, nullptr));
    if (!window) {
      glfw::checkError();
    }

    glfwMakeContextCurrent(window.get());

    while (glfwWindowShouldClose(window.get()) == GLFW_FALSE) {
      glfwWaitEvents();
    }

    return 0;
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}
