#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include <spdlog/spdlog.h>

namespace Rivet::Assets {

    // -------------------------------------------------------------------------
    // AssetCache<T>
    //
    // Generic string-keyed cache. Assets live until UnloadAll() is called.
    // T must be default-constructible and movable.
    // -------------------------------------------------------------------------
    template<typename T>
    class AssetCache
    {
    public:
        // Load an asset by key.  If the key is already cached the stored object
        // is returned immediately (cache hit); otherwise `loader` is invoked to
        // produce the value which is then inserted and returned.
        T* Load(const std::string& key, std::function<T()> loader)
        {
            auto it = m_Map.find(key);
            if (it != m_Map.end())
            {
                spdlog::debug("[AssetCache] cache hit: {}", key);
                return &it->second;
            }

            spdlog::debug("[AssetCache] cache miss — loading: {}", key);
            auto [newIt, ok] = m_Map.emplace(key, loader());
            return &newIt->second;
        }

        // Return a pointer to a cached asset, or nullptr if not yet loaded.
        T* Get(const std::string& key)
        {
            auto it = m_Map.find(key);
            return (it != m_Map.end()) ? &it->second : nullptr;
        }

        // Release every cached asset using the supplied deleter, then clear.
        void UnloadAll(std::function<void(T&)> deleter = nullptr)
        {
            if (deleter)
                for (auto& [k, v] : m_Map)
                    deleter(v);
            m_Map.clear();
        }

    private:
        std::unordered_map<std::string, T> m_Map;
    };

} // namespace Rivet::Assets
