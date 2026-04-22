# Phase 8 — Asset Manager: Plan

## Group 1 — Resource Handle System
1. Define a `Handle<T>` type (thin wrapper around `std::string` key + raw pointer or `std::shared_ptr<T>`).
2. Define a generic `AssetCache<T>` template: `std::unordered_map<std::string, T>` with `load()` and `get()` free functions.
3. Expose a `void UnloadAll()` function to clear a cache.
4. Add the cache implementation to the Rivet library under `Rivet/Assets/`.

## Group 2 — Texture Manager
1. Create `TextureManager` — thin wrapper over `AssetCache<Texture2D>`.
2. Implement `Rvt::LoadTexture(const std::string& path)` — loads via stb_image and caches; returns same object on repeated calls.
3. Implement `Rvt::GetTexture(const std::string& path)` — returns cached pointer (null if not loaded).
4. Remove direct stb_image calls from Sandbox; replace with `Rvt::LoadTexture`.

## Group 3 — Shader Manager
1. Create `ShaderManager` — thin wrapper over `AssetCache<Shader>`.
2. Implement `Rvt::LoadShader(const std::string& vertPath, const std::string& fragPath)` — compiles, links, and caches by a combined key.
3. Implement `Rvt::GetShader(const std::string& key)`.
4. Replace direct `Shader` construction in Sandbox with `Rvt::LoadShader`.
