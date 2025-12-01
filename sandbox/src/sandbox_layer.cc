#include "sandbox_layer.hh"

using namespace core;
using namespace core::utils;

SandboxLayer::SandboxLayer() {}

SandboxLayer::~SandboxLayer() {}

void SandboxLayer::OnAttach() {
  EnableGLDebugging();

  // Init here
}

void SandboxLayer::OnDetach() {
  // Shutdown here
}

void SandboxLayer::OnEvent(Event& event) {
  // Events here
}

void SandboxLayer::OnUpdate(DeltaTime dt) {
  // Render here
}

void SandboxLayer::OnImGuiRender() {
  // ImGui here
}
