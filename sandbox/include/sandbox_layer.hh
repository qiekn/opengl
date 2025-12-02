#pragma once

#include <core.h>
#include <utils.h>

#include "particle_system.hh"

class SandboxLayer : public core::Layer {
public:
  SandboxLayer();
  virtual ~SandboxLayer();

  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnEvent(core::Event& event) override;
  virtual void OnUpdate(core::DeltaTime dt) override;
  virtual void OnImGuiRender() override;

private:
  core::utils::OrthographicCameraController camera_controller_;
  ParticleProps particle_;
  ParticleSystem particle_system_;
};
;
