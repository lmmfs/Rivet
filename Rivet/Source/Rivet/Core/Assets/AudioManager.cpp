#include "AudioManager.h"

#include "../Audio/AudioEngine.h"

#include <miniaudio.h>
#include <spdlog/spdlog.h>

#include <memory>
#include <unordered_map>

namespace Rivet::Assets {

    static std::unordered_map<std::string, std::unique_ptr<Rivet::Audio::Sound>> s_SoundCache;

    Rivet::Audio::Sound* LoadSound(const std::string& path)
    {
        auto it = s_SoundCache.find(path);
        if (it != s_SoundCache.end())
        {
            spdlog::debug("[AudioManager] cache hit: {}", path);
            return it->second.get();
        }

        ma_engine* engine = Rivet::Audio::GetEngine();
        if (!engine)
        {
            spdlog::error("[AudioManager] AudioEngine not initialized");
            return nullptr;
        }

        auto sound = std::make_unique<Rivet::Audio::Sound>();
        sound->path = path;

        // MA_SOUND_FLAG_DECODE: decode to PCM at load time (lower latency at play).
        // MA_SOUND_FLAG_ASYNC:  loading happens on a background thread.
        ma_result result = ma_sound_init_from_file(
            engine,
            path.c_str(),
            MA_SOUND_FLAG_DECODE,
            nullptr,   // no group
            nullptr,   // no fence
            &sound->handle
        );

        if (result != MA_SUCCESS)
        {
            spdlog::error("[AudioManager] Failed to load '{}' (code {})", path, static_cast<int>(result));
            return nullptr;
        }

        // Default attenuation model and max distance suitable for 2D world-space
        // coordinates (pixels).  Adjust per-sound via SetPosition if needed.
        ma_sound_set_attenuation_model(&sound->handle, ma_attenuation_model_linear);
        ma_sound_set_max_distance(&sound->handle, 2000.0f);

        sound->valid = true;
        spdlog::info("[AudioManager] Loaded: {}", path);

        auto* ptr = sound.get();
        s_SoundCache.emplace(path, std::move(sound));
        return ptr;
    }

    Rivet::Audio::Sound* GetSound(const std::string& path)
    {
        auto it = s_SoundCache.find(path);
        return (it != s_SoundCache.end()) ? it->second.get() : nullptr;
    }

    void UnloadAllSounds()
    {
        for (auto& [key, sound] : s_SoundCache)
        {
            if (sound->valid)
                ma_sound_uninit(&sound->handle);
        }
        s_SoundCache.clear();
        spdlog::info("[AudioManager] All sounds unloaded");
    }

} // namespace Rivet::Assets
