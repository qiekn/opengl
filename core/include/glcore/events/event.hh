#pragma once

#include <ostream>
#include <string>

#include "glcore/core/core.hh"

namespace core {
// ----------------------------------------------------------------------------: Prepare
// clang-format off
enum class EventType {
  None = 0,
  WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
  AppTick, AppUpdate, AppRender,
  KeyPressed, KeyReleased, KeyTypes,
  MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory {
  EventCategoryNone        = 0,
  EventCategoryApplication = BIT(0),
  EventCategoryInput       = BIT(1),
  EventCategoryKeyboard    = BIT(2),
  EventCategoryMouse       = BIT(3),
  EventCategoryMouseButton = BIT(4),
};
// clang-format off

#define EVENT_CLASS_TYPE(type)                                                \
  static EventType GetStaticType() { return EventType::type; }              \
  virtual EventType GetEventType() const override { return GetStaticType(); } \
  virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
  virtual int GetCategoryFlags() const override { return category; }

// ----------------------------------------------------------------------------: Event

class Event {
public:
  bool IsHandled() const { return handled_; }
  bool& GetIsHandled() { return handled_; }

  virtual EventType GetEventType() const = 0;
  virtual const char* GetName() const = 0;
  virtual int GetCategoryFlags() const = 0;
  virtual std::string ToString() const { return GetName(); }

  bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }

private:
  bool handled_ = false;
};

// ----------------------------------------------------------------------------: Dispatcher
class EventDispatcher {
public:
  EventDispatcher(Event& event) : event_(event) {}

  template <typename T, typename F>
  bool Dispatch(const F& func) {
    if (event_.GetEventType() == T::GetStaticType()) {
      event_.GetIsHandled() = func(static_cast<T&>(event_));
      return true;
    }
    return false;
  }

private:
  Event& event_;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); }
}  // namespace core
