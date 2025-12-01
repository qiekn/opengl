#pragma once

#include "glcore/core/imgui_layer.hh"
#include "glcore/core/layer_stack.hh"
#include "glcore/core/window.hh"
#include "glcore/events/application_event.hh"
#include "glcore/events/event.hh"
#include "layer.hh"

namespace core {
class Application {
public:
  Application(const std::string& name = "OpenGL Sandbox", uint32_t width = 1280,
              uint32_t height = 720);
  virtual ~Application() = default;

  void Run();

  void OnEvent(Event& e);

  void PushLayer(Scope<Layer> layer);
  void PushOverlay(Scope<Layer> layer);

  inline auto& GetWindow() { return window_; }

  inline static Application& Get() { return *instance_; }

private:
  bool OnWindowCloseEvent(WindowCloseEvent& e);
  bool OnWindowResizeEvent(WindowResizeEvent& e);

private:
  bool is_running_ = true;
  bool is_minimized_ = false;
  Scope<Window> window_;
  ImGuiLayer* imgui_layer_;
  LayerStack layer_stack_;
  DeltaTime delta_time_;
  std::chrono::time_point<std::chrono::steady_clock> last_frame_time_ =
      std::chrono::steady_clock::now();

  static Application* instance_;
};
}  // namespace core
