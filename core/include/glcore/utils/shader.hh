#pragma once

#include <glad/gl.h>

#include <string>

namespace core {
namespace utils {

class Shader {
public:
  ~Shader();

  GLuint GetRendererID() { return renderer_id_; }

  static Shader* FromGLSLTextFiles(const std::string& vertex_shader_path,
                                   const std::string& fragment_shader_path);

private:
  Shader() = default;

  void LoadFromGLSLTextFiles(const std::string& vertex_shader_path,
                             const std::string& fragment_shader_path);
  GLuint CompileShader(GLenum type, const std::string& source);

private:
  GLuint renderer_id_;
};

}  // namespace utils
}  // namespace core
