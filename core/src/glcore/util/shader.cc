#include "glcore/utils/shader.hh"

#include <fstream>

#include "glcore/core/log.hh"

namespace core {
namespace utils {

static std::string ReadFileAsString(const std::string& filepath) {
  std::string result;
  std::ifstream in(filepath, std::ios::in | std::ios::binary);
  if (in) {
    in.seekg(0, std::ios::end);
    result.resize((size_t)in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&result[0], result.size());
    in.close();
  } else {
    LOG_ERROR("Could not open file '{0}'", filepath);
  }

  return result;
}

Shader::~Shader() { glDeleteProgram(renderer_id_); }

GLuint Shader::CompileShader(GLenum type, const std::string& source) {
  GLuint shader = glCreateShader(type);

  const GLchar* source_cstr = source.c_str();
  glShaderSource(shader, 1, &source_cstr, 0);

  glCompileShader(shader);

  GLint is_compiled = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
  if (is_compiled == GL_FALSE) {
    GLint max_length = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<GLchar> info_log(max_length);
    glGetShaderInfoLog(shader, max_length, &max_length, &info_log[0]);

    glDeleteShader(shader);

    LOG_ERROR("{0}", info_log.data());
    // HZ_CORE_ASSERT(false, "Shader compilation failure!");
  }

  return shader;
}

std::unique_ptr<Shader> Shader::FromGLSLTextFiles(
    const std::string& vertex_shader_path,
    const std::string& fragment_shader_path) {
  std::unique_ptr<Shader> shader(new Shader());
  shader->LoadFromGLSLTextFiles(vertex_shader_path, fragment_shader_path);
  return shader;
}

void Shader::LoadFromGLSLTextFiles(const std::string& vertex_shader_path,
                                   const std::string& fragment_shader_path) {
  std::string vertex_source = ReadFileAsString(vertex_shader_path);
  std::string fragment_source = ReadFileAsString(fragment_shader_path);

  GLuint program = glCreateProgram();

  GLuint vertex_shader = CompileShader(GL_VERTEX_SHADER, vertex_source);
  glAttachShader(program, vertex_shader);
  GLuint fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragment_source);
  glAttachShader(program, fragment_shader);

  glLinkProgram(program);

  GLint is_linked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int*)&is_linked);
  if (is_linked == GL_FALSE) {
    GLint max_length = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<GLchar> infoLog(max_length);
    glGetProgramInfoLog(program, max_length, &max_length, &infoLog[0]);

    glDeleteProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    LOG_ERROR("{0}", infoLog.data());
  }

  glDetachShader(program, vertex_shader);
  glDetachShader(program, fragment_shader);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  renderer_id_ = program;
}

}  // namespace utils
}  // namespace core
