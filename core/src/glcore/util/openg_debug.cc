#include "glad/gl.h"
#include "glcore/core/log.hh"
#include "glcore/utils/opengl_debug.hh"

namespace core {
namespace utils {

static DebugLogLevel s_debug_log_level = DebugLogLevel::kHighAssert;

void SetGLDebugLogLevel(DebugLogLevel level) { s_debug_log_level = level; }

void OpenGLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                      const GLchar* message, const void* user_param) {
  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
      if ((int)s_debug_log_level > 0) {
        LOG_ERROR("[OpenGL Debug HIGH] {0}", message);
        if (s_debug_log_level == DebugLogLevel::kHighAssert)
          GLCORE_ASSERT(false, "GL_DEBUG_SEVERITY_HIGH");
      }
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:
      if ((int)s_debug_log_level > 2) LOG_WARN("[OpenGL Debug MEDIUM] {0}", message);
      break;
    case GL_DEBUG_SEVERITY_LOW:
      if ((int)s_debug_log_level > 3) LOG_INFO("[OpenGL Debug LOW] {0}", message);
      break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      if ((int)s_debug_log_level > 4) LOG_TRACE("[OpenGL Debug NOTIFICATION] {0}", message);
      break;
  }
}

void EnableGLDebugging() {
  glDebugMessageCallback(OpenGLLogMessage, nullptr);
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}

}  // namespace utils
}  // namespace core
