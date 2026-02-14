#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <cstdio>
#include <cstdlib>

static void ErrorCallback(int error, const char* description) {
  std::fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

int main() {
  glfwSetErrorCallback(ErrorCallback);

  if (!glfwInit()) {
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(1200, 800, "QIEKN TEST", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwSetKeyCallback(window, KeyCallback);
  glfwMakeContextCurrent(window);

  int version = gladLoadGL(glfwGetProcAddress);
  if (!version) {
    std::fprintf(stderr, "Failed to initialize OpenGL context\n");
    glfwTerminate();
    return EXIT_FAILURE;
  }
  std::printf("OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

  glfwSwapInterval(1);

  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
}
