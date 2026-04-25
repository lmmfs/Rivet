#include "ShaderManager.h"

#include <spdlog/spdlog.h>

namespace Rivet::Assets {

    static AssetCache<Shader> s_ShaderCache;

    static std::string MakeKey(const std::string& vert, const std::string& frag)
    {
        return vert + "|" + frag;
    }

    Shader LoadShader(const std::string& vertPath, const std::string& fragPath)
    {
        const std::string key = MakeKey(vertPath, fragPath);
        Shader* cached = s_ShaderCache.Load(key, [&]() {
            return Rivet::LoadShader(vertPath.c_str(), fragPath.c_str());
        });
        return cached ? *cached : 0;
    }

    Shader GetShader(const std::string& vertPath, const std::string& fragPath)
    {
        const Shader* cached = s_ShaderCache.Get(MakeKey(vertPath, fragPath));
        return cached ? *cached : 0;
    }

    void UnloadAllShaders()
    {
        s_ShaderCache.UnloadAll([](Shader& shader) {
            Rivet::DeleteShader(shader);
        });
        spdlog::info("[Assets] All shaders unloaded");
    }

} // namespace Rivet::Assets
