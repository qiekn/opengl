#pragma once

#include <core.h>
#include <utils.h>

#include <memory>

#include "glcore/utils/shader.hh"

class HelloTriangle : public core::Layer {
public:
  HelloTriangle();
  virtual ~HelloTriangle();

  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnEvent(core::Event& event) override;
  virtual void OnUpdate(core::DeltaTime dt) override;
  virtual void OnImGuiRender() override;

  // ----------------------------------------------------------------------------: my methods
  void Update();  // Update game logic
  void Draw();    // Rendering

private:
  unsigned int vertex_array_;
  unsigned int vertex_buffer_;
  unsigned int vertex_index_;

  std::unique_ptr<core::utils::Shader> shader_;
};
