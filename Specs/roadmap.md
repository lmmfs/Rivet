# Rivet — Roadmap

Each phase is a small, shippable increment. Complete one before starting the next.

Phases 1–11 established the 2D foundation. Phases 12 onward extend Rivet into a shared-core engine with both 2D and 3D capability.

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
- [x] Choose & integrate audio library (e.g. miniaudio)
- [x] Sound loading and playback
- [x] Volume / pause / stop controls

## Phase 11 — UI Panels
- [x] Font asset loading & management
- [x] Panel component
- [x] Label component
- [x] Button component

## Phase 12 — Module Restructure
- [ ] Reorganise source into Core/, Renderer/2D/, Renderer/3D/, Physics/2D/, Physics/3D/
- [ ] Shared renderer primitives (Shader, Buffer, Texture) moved to Renderer/Common/
- [ ] Umbrella header updated to reflect module layout
- [ ] Existing 2D functionality verified unchanged after move

## Phase 13 — 3D Renderer
- [ ] 3D camera (perspective projection, look-at)
- [ ] Mesh abstraction (vertices, normals, UVs)
- [ ] Basic 3D draw call (mesh + transform)
- [ ] Depth testing enabled

## Phase 14 — 3D Physics
- [ ] Integrate Jolt Physics
- [ ] 3D physics world (init, step, shutdown)
- [ ] Static and dynamic rigid bodies (box, sphere)
- [ ] Physics-to-renderer transform sync

## Phase 15 — 3D Sandbox Demo
- [ ] Sandbox scene using 3D renderer and physics together
- [ ] Simple scene: a falling object landing on a static floor

## Phase 16 — README Update
- [ ] Project overview & description
- [ ] Build & setup instructions
- [ ] Feature list covering both 2D and 3D capabilities
