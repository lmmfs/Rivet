#pragma once

#include <string>
#include <miniaudio.h>

namespace Rivet::Audio {

    // Wraps a single miniaudio sound.  Non-copyable and non-movable because
    // ma_sound contains internal self-referential pointers.
    struct Sound
    {
        ma_sound    handle{};
        bool        valid = false;
        std::string path;

        Sound()  = default;
        ~Sound() = default;

        Sound(const Sound&)            = delete;
        Sound& operator=(const Sound&) = delete;
        Sound(Sound&&)                 = delete;
        Sound& operator=(Sound&&)      = delete;
    };

} // namespace Rivet::Audio
