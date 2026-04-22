#pragma once

#include "Sound.h"

namespace Rivet::Audio {

    // -------------------------------------------------------------------------
    // Playback controls
    // -------------------------------------------------------------------------

    void Play   (Sound& sound);
    void Stop   (Sound& sound);
    void Pause  (Sound& sound);
    void Resume (Sound& sound);

    // Loop flag.  Set before or after Play; takes effect immediately.
    void SetLoop  (Sound& sound, bool loop);

    // Volume in [0.0, 1.0].
    void SetVolume(Sound& sound, float volume);

    bool IsPlaying(const Sound& sound);

    // -------------------------------------------------------------------------
    // 2D positional audio
    //
    // Coordinates map to the same world-space units as the 2D camera.
    // z is always 0 for 2D; miniaudio's spatialization engine handles panning
    // and linear attenuation automatically.
    // -------------------------------------------------------------------------

    // Set the position of the sound emitter in world space.
    void SetPosition(Sound& sound, float x, float y);

    // Set the global listener position.  Typically updated each frame to
    // follow the camera / player.
    void SetListenerPosition(float x, float y);

} // namespace Rivet::Audio
