#include "particle_system.hh"

#include <glm/gtc/constants.hpp>

#include "random.hh"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

ParticleSystem::ParticleSystem() { particle_pool_.resize(1000); }

void ParticleSystem::OnUpdate(core::DeltaTime dt) {
  for (auto& particle : particle_pool_) {
    if (!particle.is_active) continue;

    if (particle.life_remaining <= 0.0f) {
      particle.is_active = false;
      continue;
    }

    particle.life_remaining -= dt;
    particle.position += particle.velocity * (float)dt;
    particle.rotation += 0.01f * dt;
  }
}

void ParticleSystem::OnRender(core::utils::OrthographicCamera& camera) {
  if (!quad_va_) {
    float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f};

    glCreateVertexArrays(1, &quad_va_);
    glBindVertexArray(quad_va_);

    GLuint quad_vb, quad_ib;
    glCreateBuffers(1, &quad_vb);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexArrayAttrib(quad_vb, 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    uint32_t indices[] = {0, 1, 2, 2, 3, 0};

    glCreateBuffers(1, &quad_ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    particle_shader_ = std::unique_ptr<core::utils::Shader>(core::utils::Shader::Load(
        "sandbox/assets/shader.glsl.vert", "sandbox/assets/shader.glsl.frag"));
    particle_shader_view_proj_ =
        glGetUniformLocation(particle_shader_->GetRendererID(), "u_ViewProj");
    particle_shader_transform_ =
        glGetUniformLocation(particle_shader_->GetRendererID(), "u_Transform");
    particle_shader_color_ = glGetUniformLocation(particle_shader_->GetRendererID(), "u_Color");
  }

  if (!particle_shader_ || particle_shader_->GetRendererID() == 0) {
    return;
  }

  glUseProgram(particle_shader_->GetRendererID());
  glUniformMatrix4fv(particle_shader_view_proj_, 1, GL_FALSE,
                     glm::value_ptr(camera.GetViewProjectionMatrix()));

  for (auto& particle : particle_pool_) {
    if (!particle.is_active) continue;

    // Fade away particles
    float life = particle.life_remaining / particle.life_time;
    glm::vec4 color = glm::lerp(particle.color_end, particle.color_begin, life);
    // color.a = color.a * life;

    float size = glm::lerp(particle.size_end, particle.size_begin, life);

    // Render
    glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), {particle.position.x, particle.position.y, 0.0f}) *
        glm::rotate(glm::mat4(1.0f), particle.rotation, {0.0f, 0.0f, 1.0f}) *
        glm::scale(glm::mat4(1.0f), {size, size, 1.0f});
    glUniformMatrix4fv(particle_shader_transform_, 1, GL_FALSE, glm::value_ptr(transform));
    glUniform4fv(particle_shader_color_, 1, glm::value_ptr(color));
    glBindVertexArray(quad_va_);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  }
}

void ParticleSystem::Emit(const ParticleProps& particle_props) {
  Particle& particle = particle_pool_[pool_index_];
  particle.is_active = true;
  particle.position = particle_props.position;
  particle.rotation = Random::Float() * 2.0f * glm::pi<float>();

  // Velocity
  particle.velocity = particle_props.velocity;
  particle.velocity.x += particle_props.velocity_variation.x * (Random::Float() - 0.5f);
  particle.velocity.y += particle_props.velocity_variation.y * (Random::Float() - 0.5f);

  // Color
  particle.color_begin = particle_props.color_begin;
  particle.color_end = particle_props.color_end;

  particle.life_time = particle_props.life_time;
  particle.life_remaining = particle_props.life_time;
  particle.size_begin =
      particle_props.size_begin + particle_props.size_variation * (Random::Float() - 0.5f);
  particle.size_end = particle_props.size_end;

  pool_index_ = --pool_index_ % particle_pool_.size();
}
