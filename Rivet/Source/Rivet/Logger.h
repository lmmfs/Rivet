#pragma once

#include <spdlog/spdlog.h>
#include <memory>

namespace Rivet::Log {
    void Init();
    std::shared_ptr<spdlog::logger>& GetCoreLogger();
    std::shared_ptr<spdlog::logger>& GetClientLogger();
}

// Always enabled: info, warn, error
#define RVT_CORE_INFO(...)  ::Rivet::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RVT_CORE_WARN(...)  ::Rivet::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RVT_CORE_ERROR(...) ::Rivet::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RVT_INFO(...)       ::Rivet::Log::GetClientLogger()->info(__VA_ARGS__)
#define RVT_WARN(...)       ::Rivet::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RVT_ERROR(...)      ::Rivet::Log::GetClientLogger()->error(__VA_ARGS__)

// Debug-only
#ifndef NDEBUG
    #define RVT_CORE_DEBUG(...) ::Rivet::Log::GetCoreLogger()->debug(__VA_ARGS__)
    #define RVT_DEBUG(...)      ::Rivet::Log::GetClientLogger()->debug(__VA_ARGS__)
#else
    #define RVT_CORE_DEBUG(...)
    #define RVT_DEBUG(...)
#endif
