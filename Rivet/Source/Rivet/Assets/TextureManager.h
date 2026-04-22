#pragma once

#include "AssetCache.h"
#include "../Renderer/Texture.h"

namespace Rivet::Assets {

    // -------------------------------------------------------------------------
    // TextureManager
    //
    // Wraps AssetCache<Texture2D>.  Textures are loaded once and shared;
    // calling LoadTexture with the same path returns the same cached object.
    // Call UnloadAllTextures() at shutdown to release GPU resources.
    // -------------------------------------------------------------------------

    // Load (or retrieve) a texture by file path.
    // Returns a pointer into the cache — valid until UnloadAllTextures().
    Texture2D* LoadTexture(const std::string& path);

    // Return a pointer to a cached texture, or nullptr if not yet loaded.
    const Texture2D* GetTexture(const std::string& path);

    // Release all cached textures and free their GPU resources.
    void UnloadAllTextures();

} // namespace Rivet::Assets
