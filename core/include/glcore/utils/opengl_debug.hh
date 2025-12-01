#pragma once

#include <glad/gl.h>

namespace core {
namespace utils {
enum class DebugLogLevel {
  kNone = 0,
  kHighAssert = 1,
  kHigh = 2,
  kMedium = 3,
  kLow = 4,
  kNotification = 5
};

void EnableGLDebugging();
void SetGLDebugLogLevel(DebugLogLevel level);
void OpenGLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                      const GLchar* message, const void* userParam);
}  // namespace utils
}  // namespace core
