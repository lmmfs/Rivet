# Rivet — Roadmap

Each phase is a small, shippable increment. Complete one before starting the next.

## Phase 1 — Foundation (done)
- [x] CMake project structure (Rivet static lib + Sandbox executable)
- [x] Fetch dependencies (GLFW, GLAD, GLM, spdlog, stb_image)
- [x] Precompiled header (Rvtph.h)
- [x] Window class (create, update, destroy, vsync)
- [x] Umbrella header (Rivet/Rivet.h)

## Phase 2 — Core Loop & Input
- [ ] Basic application loop abstraction (init / update / shutdown)
- [ ] Keyboard input polling
- [ ] Mouse input polling (position, buttons)
- [ ] Window resize callback handling

## Phase 3 — Events
- [ ] Event base class / type enum
- [ ] Window events (close, resize, focus)
- [ ] Input events (key, mouse)
- [ ] Event dispatcher

## Phase 4 — Basic Renderer
- [ ] Shader loading & compilation (vertex + fragment)
- [ ] Shader program linking and uniform setters
- [ ] VAO/VBO/EBO abstraction
- [ ] Clear color & viewport management

## Phase 5 — 2D Drawing
- [ ] Textured quad rendering
- [ ] Sprite batching
- [ ] Basic camera (2D orthographic)
- [ ] Texture loading via stb_image

## Phase 6 — Asset Manager
- [ ] Resource handle system (load once, share)
- [ ] Texture manager
- [ ] Shader manager

## Phase 7 — Physics
- [ ] Basic 2D collision detection (AABB)
- [ ] Simple rigid-body response
- [ ] Evaluate integration of a physics library

## Phase 8 — Audio
- [ ] Choose & integrate audio library (e.g. miniaudio)
- [ ] Sound loading and playback
- [ ] Volume / pause / stop controls
