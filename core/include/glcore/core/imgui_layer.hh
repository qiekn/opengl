#pragma once

#include "layer.hh"

namespace core {
class ImGuiLayer : public Layer {
public:
  ImGuiLayer();
  virtual ~ImGuiLayer();

  void OnAttach() override;
  void OnDetach() override;
  void OnEvent(Event& e) override;
  void OnImGuiRender() override;

  void Begin();
  void End();
};
}  // namespace core
