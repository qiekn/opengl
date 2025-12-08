#include "hello_triangle.hh"

#include "core.h"
#include "glcore/utils/shader.hh"

using namespace core;
using namespace core::utils;

HelloTriangle::HelloTriangle() {}

HelloTriangle::~HelloTriangle() {}

void HelloTriangle::OnAttach() {
  EnableGLDebugging();

  // ----------------------------------------------------------------------------: vertices data
  float vertices[] = {
      -0.5f, -0.5f,  // left
      0.5f,  -0.5f,  // right
      0.0f,  0.5f,   // top
  };

  // ----------------------------------------------------------------------------: vao
  glGenVertexArrays(1, &vertex_array_);
  glBindVertexArray(vertex_array_);

  // ----------------------------------------------------------------------------: vbo
  glGenBuffers(1, &vertex_buffer_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);

  // VBO transfer data to gpu
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // VBO tell gpu data memory layout
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // ----------------------------------------------------------------------------: shader
  shader_ = Shader::FromGLSLTextFiles("assets/shaders/example.vert", "assets/shaders/example.frag");
}

void HelloTriangle::OnDetach() {}

void HelloTriangle::OnEvent(Event& event) {}

void HelloTriangle::OnUpdate(DeltaTime dt) {
  Update();
  Draw();
}

void HelloTriangle::OnImGuiRender() {}

// ----------------------------------------------------------------------------: My funcs

void HelloTriangle::Update() {}

void HelloTriangle::Draw() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(shader_->GetRendererID());
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
