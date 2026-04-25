#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Rivet::Log {

    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;

    void Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        s_CoreLogger = spdlog::stdout_color_mt("RIVET");
        s_ClientLogger = spdlog::stdout_color_mt("APP");

#ifndef NDEBUG
        s_CoreLogger->set_level(spdlog::level::debug);
        s_ClientLogger->set_level(spdlog::level::debug);
#else
        s_CoreLogger->set_level(spdlog::level::info);
        s_ClientLogger->set_level(spdlog::level::info);
#endif
    }

    std::shared_ptr<spdlog::logger>& GetCoreLogger()   { return s_CoreLogger; }
    std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

}
