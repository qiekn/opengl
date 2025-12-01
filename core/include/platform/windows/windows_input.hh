#pragma once

#include "glcore/core/input.hh"

namespace core {
class WindowsInput : public Input {
protected:
  virtual bool IsKeyPressedImpl(int key_code) const override;

  virtual bool IsMouseButtonPressedImpl(int mouseButton) const override;

  virtual std::pair<float, float> GetMousePosImpl() const override;
  virtual float GetMouseXImpl() const override;
  virtual float GetMouseYImpl() const override;
};
}  // namespace core
