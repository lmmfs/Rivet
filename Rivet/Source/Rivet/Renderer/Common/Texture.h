#pragma once

#include <cstdint>
#include <string>

namespace Rivet {

    struct Texture2D
    {
        uint32_t id       = 0;
        int      width    = 0;
        int      height   = 0;
        int      channels = 0;
    };

    // Load a texture from disk via stb_image (forced to RGBA).
    // Returns a Texture2D with id == 0 on failure.
    Texture2D LoadTexture(const std::string& path);

    // Release the GPU resource.
    void UnloadTexture(Texture2D& tex);

} // namespace Rivet
