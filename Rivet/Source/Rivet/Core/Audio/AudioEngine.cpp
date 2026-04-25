#include "AudioEngine.h"

#include <miniaudio.h>
#include <spdlog/spdlog.h>

namespace Rivet::Audio {

    static ma_engine s_Engine{};
    static bool      s_Initialized = false;

    void Init()
    {
        ma_engine_config cfg = ma_engine_config_init();
        ma_result result = ma_engine_init(&cfg, &s_Engine);
        if (result != MA_SUCCESS)
        {
            spdlog::error("[AudioEngine] Failed to initialize (code {})", static_cast<int>(result));
            return;
        }
        s_Initialized = true;
        spdlog::info("[AudioEngine] Initialized");
    }

    void Shutdown()
    {
        if (s_Initialized)
        {
            ma_engine_uninit(&s_Engine);
            s_Initialized = false;
            spdlog::info("[AudioEngine] Shutdown");
        }
    }

    ma_engine* GetEngine()
    {
        return s_Initialized ? &s_Engine : nullptr;
    }

} // namespace Rivet::Audio
