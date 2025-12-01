#include "glcore/utils/orthographic_camera_controller.hh"

#include "glcore/core/core.hh"
#include "glcore/core/input.hh"
#include "glcore/core/key_codes.hh"

namespace core {
namespace utils {

OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
    : asprect_ratio_(aspectRatio),
      camera_(-asprect_ratio_ * zoom_level_, asprect_ratio_ * zoom_level_, -zoom_level_,
              zoom_level_),
      rotation_(rotation) {}

void OrthographicCameraController::OnUpdate(DeltaTime dt) {
  if (Input::IsKeyPressed(KEY_A)) {
    camera_postion_.x -= cos(glm::radians(camera_rotation_)) * camera_translation_speed_ * dt;
    camera_postion_.y -= sin(glm::radians(camera_rotation_)) * camera_translation_speed_ * dt;
  } else if (Input::IsKeyPressed(KEY_D)) {
    camera_postion_.x += cos(glm::radians(camera_rotation_)) * camera_translation_speed_ * dt;
    camera_postion_.y += sin(glm::radians(camera_rotation_)) * camera_translation_speed_ * dt;
  }

  if (Input::IsKeyPressed(KEY_W)) {
    camera_postion_.x += -sin(glm::radians(camera_rotation_)) * camera_translation_speed_ * dt;
    camera_postion_.y += cos(glm::radians(camera_rotation_)) * camera_translation_speed_ * dt;
  } else if (Input::IsKeyPressed(KEY_S)) {
    camera_postion_.x -= -sin(glm::radians(camera_rotation_)) * camera_translation_speed_ * dt;
    camera_postion_.y -= cos(glm::radians(camera_rotation_)) * camera_translation_speed_ * dt;
  }

  if (rotation_) {
    if (Input::IsKeyPressed(KEY_Q)) camera_rotation_ += camera_rotation_speed_ * dt;
    if (Input::IsKeyPressed(KEY_E)) camera_rotation_ -= camera_rotation_speed_ * dt;

    if (camera_rotation_ > 180.0f)
      camera_rotation_ -= 360.0f;
    else if (camera_rotation_ <= -180.0f)
      camera_rotation_ += 360.0f;

    camera_.SetRotation(camera_rotation_);
  }

  camera_.SetPosition(camera_postion_);

  camera_translation_speed_ = zoom_level_;
}

void OrthographicCameraController::OnEvent(Event& e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<MouseScrollEvent>(
      GLCORE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
  dispatcher.Dispatch<WindowResizeEvent>(
      GLCORE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrollEvent& e) {
  zoom_level_ -= e.GetMouseYOffset() * 0.25f;
  zoom_level_ = std::max(zoom_level_, 0.25f);
  camera_.SetProjection(-asprect_ratio_ * zoom_level_, asprect_ratio_ * zoom_level_, -zoom_level_,
                        zoom_level_);
  return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e) {
  asprect_ratio_ = (float)e.GetWidth() / (float)e.GetHeight();
  camera_.SetProjection(-asprect_ratio_ * zoom_level_, asprect_ratio_ * zoom_level_, -zoom_level_,
                        zoom_level_);
  return false;
}

}  // namespace utils
}  // namespace core
