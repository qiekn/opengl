#include "platform/windows/windows_input.hh"

#include "glcore/core/application.hh"
#include "glcore/core/core.hh"
#include "glcore/core/input.hh"
#include "GLFW/glfw3.h"

namespace core {

Scope<Input> Input::instance_ = std::make_unique<WindowsInput>();

bool WindowsInput::IsKeyPressedImpl(int key_code) const {
  auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
  auto state = glfwGetKey(window, key_code);
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInput::IsMouseButtonPressedImpl(int button) const {
  auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
  auto state = glfwGetMouseButton(window, button);
  return state == GLFW_PRESS;
}

std::pair<float, float> WindowsInput::GetMousePosImpl() const {
  auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  return {(float)x, (float)y};
}

float WindowsInput::GetMouseXImpl() const {
  auto [x, y] = GetMousePosImpl();
  return x;
}

float WindowsInput::GetMouseYImpl() const {
  auto [x, y] = GetMousePosImpl();
  return y;
}

}  // namespace core
