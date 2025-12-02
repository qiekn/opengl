#pragma once

#include <core.h>
#include <utils.h>

struct ParticleProps {
  glm::vec2 position;
  glm::vec2 velocity, velocity_variation;
  glm::vec4 color_begin, color_end;
  float size_begin, size_end, size_variation;
  float life_time = 1.0f;
};

class ParticleSystem {
public:
  ParticleSystem();

  void OnUpdate(core::DeltaTime dt);
  void OnRender(core::utils::OrthographicCamera& camera);

  void Emit(const ParticleProps& particle_props);

private:
  struct Particle {
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec4 color_begin, color_end;
    float rotation = 0.0f;
    float size_begin, size_end;

    float life_time = 1.0f;
    float life_remaining = 0.0f;

    bool is_active = false;
  };
  std::vector<Particle> particle_pool_;
  uint32_t pool_index_ = 999;

  GLuint quad_va_ = 0;
  std::unique_ptr<core::utils::Shader> particle_shader_;
  GLint particle_shader_view_proj_, particle_shader_transform_, particle_shader_color_;
};
