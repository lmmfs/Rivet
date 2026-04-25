#include "Audio.h"
#include "AudioEngine.h"

#include <miniaudio.h>
#include <spdlog/spdlog.h>

namespace Rivet::Audio {

    // -------------------------------------------------------------------------
    // Playback
    // -------------------------------------------------------------------------

    void Play(Sound& sound)
    {
        if (!sound.valid) return;
        ma_sound_seek_to_pcm_frame(&sound.handle, 0);
        ma_sound_start(&sound.handle);
    }

    void Stop(Sound& sound)
    {
        if (!sound.valid) return;
        ma_sound_stop(&sound.handle);
        ma_sound_seek_to_pcm_frame(&sound.handle, 0);
    }

    void Pause(Sound& sound)
    {
        if (!sound.valid) return;
        ma_sound_stop(&sound.handle);
    }

    void Resume(Sound& sound)
    {
        if (!sound.valid) return;
        ma_sound_start(&sound.handle);
    }

    void SetLoop(Sound& sound, bool loop)
    {
        if (!sound.valid) return;
        ma_sound_set_looping(&sound.handle, loop ? MA_TRUE : MA_FALSE);
    }

    void SetVolume(Sound& sound, float volume)
    {
        if (!sound.valid) return;
        ma_sound_set_volume(&sound.handle, volume);
    }

    bool IsPlaying(const Sound& sound)
    {
        if (!sound.valid) return false;
        return ma_sound_is_playing(&sound.handle) == MA_TRUE;
    }

    // -------------------------------------------------------------------------
    // 2D positional audio
    // -------------------------------------------------------------------------

    void SetPosition(Sound& sound, float x, float y)
    {
        if (!sound.valid) return;
        // Enable spatialization if not already and position the emitter.
        ma_sound_set_spatialization_enabled(&sound.handle, MA_TRUE);
        ma_sound_set_position(&sound.handle, x, y, 0.0f);
    }

    void SetListenerPosition(float x, float y)
    {
        ma_engine* engine = GetEngine();
        if (!engine) return;
        ma_engine_listener_set_position(engine, 0, x, y, 0.0f);
    }

} // namespace Rivet::Audio
