#include "glcore/core/application.hh"

#include "glcore/core/core.hh"
#include "glcore/core/log.hh"

namespace core {

Application* Application::instance_ = nullptr;

Application::Application(const std::string& name, uint32_t width, uint32_t height) {
  GLCORE_ASSERT(!s_Instance, "Application already exists!");
  if (!instance_) {
    Log::Init();
  }

  instance_ = this;

  window_ = Window::Create({name, width, height});
  window_->SetEventCallback(GLCORE_BIND_EVENT_FN(Application::OnEvent));

  auto imgui_layer = CreateScope<ImGuiLayer>();
  imgui_layer_ = imgui_layer.get();
  PushOverlay(std::move(imgui_layer));
}

void Application::Run() {
  while (is_running_) {
    auto time = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration<float>(time - last_frame_time_).count();
    auto timestep = DeltaTime(diff);

    if (!is_minimized_) {
      for (auto& layer : layer_stack_) {
        layer->OnUpdate(timestep);
      }
    }

    imgui_layer_->Begin();  // this is dirty, but it works
    {
      for (auto& layer : layer_stack_) {
        layer->OnImGuiRender();
      }
    }
    imgui_layer_->End();

    window_->OnUpdate();
    last_frame_time_ = time;
  }
}

void Application::OnEvent(Event& e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(GLCORE_BIND_EVENT_FN(Application::OnWindowCloseEvent));
  dispatcher.Dispatch<WindowResizeEvent>(GLCORE_BIND_EVENT_FN(Application::OnWindowResizeEvent));

  for (auto it = layer_stack_.end(); it != layer_stack_.begin();) {
    (*--it)->OnEvent(e);
    if (e.IsHandled()) break;
  }
}

bool Application::OnWindowCloseEvent(WindowCloseEvent& e) {
  is_running_ = false;
  return true;
}

bool Application::OnWindowResizeEvent(WindowResizeEvent& e) {
  if (e.GetWidth() == 0 || e.GetHeight() == 0) {
    is_minimized_ = true;
    return false;
  }

  is_minimized_ = false;
  return false;
}

void Application::PushLayer(Scope<Layer> layer) {
  layer->OnAttach();
  layer_stack_.push_layer(std::move(layer));
}

void Application::PushOverlay(Scope<Layer> layer) {
  layer->OnAttach();
  layer_stack_.push_overlay(std::move(layer));
}

}  // namespace core
