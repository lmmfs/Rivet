# Rivet — Roadmap

Each phase is a small, shippable increment. Complete one before starting the next.

## Phase 1 — Foundation (done)
- [x] CMake project structure (Rivet static lib + Sandbox executable)
- [x] Fetch dependencies (GLFW, GLAD, GLM, spdlog, stb_image)
- [x] Precompiled header (Rvtph.h)
- [x] Window class (create, update, destroy, vsync)
- [x] Umbrella header (Rivet/Rivet.h)

## Phase 2 — Core Loop & Input
- [x] Basic application loop abstraction (init / update / shutdown)
- [x] Keyboard input polling
- [x] Mouse input polling (position, buttons)
- [x] Window resize callback handling

## Phase 3 — Events
- [x] Event base class / type enum
- [x] Window events (close, resize, focus)
- [x] Input events (key, mouse)
- [x] Event dispatcher (polling queue)

## Phase 4 — Basic Renderer
- [x] Shader loading & compilation (vertex + fragment)
- [x] Shader program linking and uniform setters
- [x] VAO/VBO/EBO abstraction
- [x] Clear color & viewport management

## Phase 5 — Buffer Layouts
- [x] ShaderDataType enum
- [x] BufferElement struct (name, type, size, offset, normalized)
- [x] BufferLayout collection (auto stride & offsets)
- [x] Apply layout to vertex array

## Phase 6 — GUI (Dear ImGui)
- [x] Dear ImGui dependency integration
- [x] GUI init / shutdown
- [x] Per-frame GUI begin / end
- [x] Sandbox ImGui demo

## Phase 7 — 2D Drawing
- [x] Textured quad rendering
- [x] Sprite batching
- [x] Basic camera (2D orthographic)
- [x] Texture loading via stb_image

## Phase 8 — Asset Manager
- [x] Resource handle system (load once, share)
- [x] Texture manager
- [x] Shader manager

## Phase 9 — Physics
- [x] Basic 2D collision detection (AABB)
- [x] Simple rigid-body response
- [x] Evaluate integration of a physics library

## Phase 10 — Audio
- [ ] Choose & integrate audio library (e.g. miniaudio)
- [ ] Sound loading and playback
- [ ] Volume / pause / stop controls
