#pragma once

#include "../Audio/Sound.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace Rivet::Assets {

    // -------------------------------------------------------------------------
    // AudioManager
    //
    // Loads audio files once and shares ownership via raw pointers into the
    // internal map.  Pointers remain valid until UnloadAllSounds() is called.
    //
    // Pattern mirrors TextureManager / ShaderManager.
    // -------------------------------------------------------------------------

    // Load (or retrieve) a sound by file path.
    // Returns a pointer into the cache — valid until UnloadAllSounds().
    // Returns nullptr on failure (error is logged).
    Rivet::Audio::Sound* LoadSound(const std::string& path);

    // Return a pointer to a cached sound, or nullptr if not yet loaded.
    Rivet::Audio::Sound* GetSound(const std::string& path);

    // Release all cached sounds (ma_sound_uninit each one).
    void UnloadAllSounds();

} // namespace Rivet::Assets
