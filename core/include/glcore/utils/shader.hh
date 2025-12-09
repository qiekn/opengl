#pragma once

#include <glad/gl.h>

#include <memory>
#include <string>

namespace core {
namespace utils {

class Shader {
public:
  ~Shader();

  GLuint GetRendererID() { return renderer_id_; }

  /**
   * @brief Creates and loads a Shader instance from GLSL source files.
   *
   * @param vertex_shader_path   The file path to the vertex shader.
   * @param fragment_shader_path The file path to the fragment shader.
   * @return A unique_ptr owning the created Shader instance.
   */
  static std::unique_ptr<Shader> Load(const std::string& vertex_shader_path,
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
