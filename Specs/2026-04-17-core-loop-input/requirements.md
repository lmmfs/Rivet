# Phase 2 — Core Loop & Input: Requirements

## Scope

Implement a minimal, usable application loop and input polling API for Rivet. This is the first
public-facing API surface; every decision here sets the ergonomic tone for the rest of the engine.

### In scope
- Application lifecycle free functions (`Init`, `ShouldClose`, `BeginFrame`, `EndFrame`, `Shutdown`)
- Keyboard polling (down / pressed / released, frame-accurate)
- Mouse polling (position, delta, button down / pressed / released)
- Window resize handling with automatic viewport update
- Logging macros: `RVT_CORE_INFO` / `RVT_CORE_ERROR` (engine) and `RVT_INFO` / `RVT_ERROR` (client)
- Exposure of all new symbols through `Rivet/Rivet.h`

### Out of scope
- Gamepad / joystick input
- Multi-window support
- Text / character input events (deferred to Phase 3 Events)
- Raw input or platform-specific hooks

---

## API Style Decisions

**Application loop — free functions (raylib-style)**  
No subclassable `Application` base class. The user writes their own `main()` and calls Rivet
free functions explicitly. This keeps the API transparent and avoids hidden magic.

```cpp
// Intended usage
int main() {
    Rivet::Init("My Game", 1280, 720);
    while (!Rivet::ShouldClose()) {
        Rivet::BeginFrame();
        // user code
        Rivet::EndFrame();
    }
    Rivet::Shutdown();
}
```

**Input — stateless free functions**  
Input state is owned internally by Rivet (static or module-private). Users call free functions;
there is no `InputManager` object to instantiate or pass around.

```cpp
if (Rivet::IsKeyPressed(Rivet::Key::Space)) { /* jump */ }
glm::vec2 cursor = Rivet::GetMousePosition();
```

**Logging — two-logger macro system**  
Two spdlog loggers are created at `Rivet::Init()` time and accessed only through macros:

| Macro | Logger | Intended audience |
|---|---|---|
| `RVT_CORE_INFO(...)` | `RVT_CORE_LOGGER` | Engine internals |
| `RVT_CORE_ERROR(...)` | `RVT_CORE_LOGGER` | Engine internals |
| `RVT_INFO(...)` | `RVT_CLIENT_LOGGER` | Sandbox / game code |
| `RVT_ERROR(...)` | `RVT_CLIENT_LOGGER` | Sandbox / game code |

Only `info` and `error` levels are exposed in this phase. Macros expand to nothing in release
builds (`NDEBUG` defined). Raw `spdlog::` calls must not appear in engine code after this task.

```cpp
// Engine side
RVT_CORE_INFO("Window created: {}x{}", width, height);
RVT_CORE_ERROR("GLFW init failed");

// Sandbox / game side
RVT_INFO("Frame {}", frameCount);
RVT_ERROR("Asset not found: {}", path);
```

---

## Context & Constraints

- **Language**: C++23, all new files follow existing project conventions.
- **Build**: added headers go under `Rivet/Source/Rivet/`, implementation files under
  `Rivet/Source/`; `CMakeLists.txt` updated accordingly.
- **Dependencies**: only GLFW callbacks and GLM types — no new external libraries.
- **Logging**: two named spdlog loggers initialised in `Log::Init()`; accessed exclusively via
  macros (`RVT_CORE_*` / `RVT_*`). No logging in hot-path polling functions.
- **Input frame timing**: previous-state snapshot is updated at the top of `BeginFrame()` so
  pressed/released are consistent for the entire frame.
- **Viewport**: the framebuffer-size callback calls `glViewport` directly; no abstraction layer
  beyond the `Window` class.
- **Mission alignment**: API stays procedural and minimal per the raylib-style principle;
  no feature is added that is not listed in the roadmap for this phase.
