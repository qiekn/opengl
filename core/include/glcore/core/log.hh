#pragma once

#include "core.hh"
#include "spdlog/spdlog.h"  // IWYU pragma: keep

namespace core {
class Log {
public:
  Log() = default;
  virtual ~Log() = default;

  static void Init();
  inline static Ref<spdlog::logger>& GetEngineLogger() { return engine_logger_; }
  inline static Ref<spdlog::logger>& GetClientLogger() { return client_logger_; }

private:
  static Ref<spdlog::logger> engine_logger_;
  static Ref<spdlog::logger> client_logger_;
};
}  // namespace core

// clang-format off
#define CORE_LOG_TRACE(...) ::core::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define CORE_LOG_INFO(...)  ::core::Log::GetEngineLogger()->info(__VA_ARGS__)
#define CORE_LOG_WARN(...)  ::core::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define CORE_LOG_ERROR(...) ::core::Log::GetEngineLogger()->error(__VA_ARGS__)
#define CORE_LOG_FATAL(...) ::core::Log::GetEngineLogger()->fatal(__VA_ARGS__)

#define LOG_TRACE(...) ::core::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)  ::core::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)  ::core::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::core::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...) ::core::Log::GetClientLogger()->fatal(__VA_ARGS__)
// clang-format on

#define ENABLE_ASSERT 1

#if ENABLE_ASSERT
#define CORE_ASSERT(x, ...)                              \
  if (!(x)) {                                            \
    CORE_LOG_ERROR("Assertion failed: {}", __VA_ARGS__); \
    std::abort();                                        \
  }
#else
#define CORE_ASSERT(x, ...)
#endif
