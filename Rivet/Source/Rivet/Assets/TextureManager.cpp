#include "TextureManager.h"

#include <spdlog/spdlog.h>

namespace Rivet::Assets {

    static AssetCache<Texture2D> s_TextureCache;

    Texture2D* LoadTexture(const std::string& path)
    {
        return s_TextureCache.Load(path, [&path]() {
            return Rivet::LoadTexture(path);
        });
    }

    const Texture2D* GetTexture(const std::string& path)
    {
        return s_TextureCache.Get(path);
    }

    void UnloadAllTextures()
    {
        s_TextureCache.UnloadAll([](Texture2D& tex) {
            Rivet::UnloadTexture(tex);
        });
        spdlog::info("[Assets] All textures unloaded");
    }

} // namespace Rivet::Assets
