# Phase 8 — Asset Manager: Requirements

## Scope
Introduce a centralized asset management layer so that textures and shaders are loaded once and shared. Consumers always go through the manager — no raw stb_image or `Shader` constructor calls in Sandbox or game code.

## In Scope
- Generic, template-based cache (`AssetCache<T>`).
- `TextureManager` and `ShaderManager` backed by that cache.
- Free-function (raylib-style) public API exposed from the `Rvt` namespace.
- Manual unload only (`UnloadAll()`); no automatic ref-counting.

## Out of Scope
- Hot-reload (file-watching).
- Ref-counted or automatic eviction.
- Async / background loading.
- Asset packing / virtual file system.

## Design Decisions

| Decision | Choice | Rationale |
|---|---|---|
| Cache key | `std::string` (file path or `"vert|frag"` for shaders) | Simplest; paths are already unique identifiers |
| Ownership | Cache owns the asset (`std::unordered_map<string, T>`) | Simple lifetime — assets live until `UnloadAll()` |
| API style | Singleton manager + free functions in `Rvt::` namespace | Consistent with mission (raylib-style, no object passing) |
| Ref-counting | None — manual unload only | Avoids complexity; games rarely hot-swap assets at runtime |

## Context
- Follows the mission principle: *Hand-roll first* — no external asset-management library.
- The `Texture2D` and `Shader` types are already defined in the engine from Phase 4 & 7.
- The Sandbox currently constructs `Shader` and calls stb_image directly; these will be replaced.
