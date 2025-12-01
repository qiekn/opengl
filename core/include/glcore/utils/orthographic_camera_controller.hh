#pragma once

#include "glcore/core/deltatime.hh"
#include "glcore/events/application_event.hh"
#include "glcore/events/mouse_event.hh"
#include "glcore/utils/orthographic_camera.hh"

namespace core {
namespace utils {
struct OrthographicCameraBounds {
  float left, right;
  float bottom, top;

  float GetWidth() { return right - left; }
  float GetHeight() { return top - bottom; }
};

class OrthographicCameraController {
public:
  OrthographicCameraController(float aspectRatio, bool rotation = false);

  void OnUpdate(DeltaTime dt);
  void OnEvent(Event& e);

  OrthographicCamera& GetCamera() { return camera_; }
  const OrthographicCamera& GetCamera() const { return camera_; }

  float GetZoomLevel() const { return zoom_level_; }
  void SetZoomLevel(float level) { zoom_level_ = level; }

  const OrthographicCameraBounds& GetBounds() const { return bounds_; }

private:
  bool OnMouseScrolled(MouseScrollEvent& e);
  bool OnWindowResized(WindowResizeEvent& e);

private:
  float asprect_ratio_;
  float zoom_level_ = 1.0f;
  OrthographicCameraBounds bounds_;
  OrthographicCamera camera_;

  bool rotation_;

  glm::vec3 camera_postion_ = {0.0f, 0.0f, 0.0f};
  float camera_rotation_ = 0.0f;  // In degrees, in the anti-clockwise direction
  float camera_translation_speed_ = 5.0f, camera_rotation_speed_ = 180.0f;
};
}  // namespace utils
}  // namespace core
