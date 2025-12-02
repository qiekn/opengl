#include "sandbox_layer.hh"

using namespace core;
using namespace core::utils;

SandboxLayer::SandboxLayer() : camera_controller_(16.0f / 9.0f) {}

SandboxLayer::~SandboxLayer() {}

void SandboxLayer::OnAttach() {
  EnableGLDebugging();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Init here
  particle_.ColorBegin = {254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f};
  particle_.ColorEnd = {254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f};
  particle_.SizeBegin = 0.5f, particle_.SizeVariation = 0.3f, particle_.SizeEnd = 0.0f;
  particle_.LifeTime = 1.0f;
  particle_.Velocity = {0.0f, 0.0f};
  particle_.VelocityVariation = {3.0f, 1.0f};
  particle_.Position = {0.0f, 0.0f};
}

void SandboxLayer::OnDetach() {
  // Shutdown here
}

void SandboxLayer::OnEvent(Event& event) {
  // Events here
  camera_controller_.OnEvent(event);

  if (event.GetEventType() == EventType::WindowResize) {
    WindowResizeEvent& e = (WindowResizeEvent&)event;
    glViewport(0, 0, e.GetWidth(), e.GetHeight());
  }
}

void SandboxLayer::OnUpdate(DeltaTime dt) {
  camera_controller_.OnUpdate(dt);

  // Render here

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  // glClearColor(0, 0, 0, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  if (core::Input::IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    auto [x, y] = Input::GetMousePos();
    auto width = core::Application::Get().GetWindow()->GetWidth();
    auto height = core::Application::Get().GetWindow()->GetHeight();

    auto bounds = camera_controller_.GetBounds();
    auto pos = camera_controller_.GetCamera().GetPosition();
    x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
    y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
    particle_.Position = {x + pos.x, y + pos.y};
    for (int i = 0; i < 5; i++) particle_system_.Emit(particle_);
  }

  particle_system_.OnUpdate(dt);
  particle_system_.OnRender(camera_controller_.GetCamera());
}

void SandboxLayer::OnImGuiRender() {
  // ImGui here

  ImGui::Begin("Settings");
  ImGui::ColorEdit4("Birth Color", glm::value_ptr(particle_.ColorBegin));
  ImGui::ColorEdit4("Death Color", glm::value_ptr(particle_.ColorEnd));
  ImGui::DragFloat("Life Time", &particle_.LifeTime, 0.1f, 0.0f, 1000.0f);
  ImGui::End();
}
