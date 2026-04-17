# Phase 2 — Core Loop & Input: Plan

## Group 1 — Application Lifecycle

1. Define `Rivet::Init()` — initialise GLFW window and GL context via the existing `Window` class.
2. Define `Rivet::ShouldClose()` — thin wrapper over the window close flag.
3. Define `Rivet::BeginFrame()` — poll events, clear the back-buffer.
4. Define `Rivet::EndFrame()` — swap buffers.
5. Define `Rivet::Shutdown()` — destroy window and terminate GLFW.
6. Wire up Sandbox `Main.cpp` to use the new lifecycle API and verify it compiles and runs.

## Group 2 — Keyboard Polling

7. Declare `enum class Key` mapping named keys to GLFW key codes.
8. Implement `Rivet::IsKeyDown(Key key)` — returns true while the key is held.
9. Implement `Rivet::IsKeyPressed(Key key)` — returns true on the first frame the key is down.
10. Implement `Rivet::IsKeyReleased(Key key)` — returns true on the frame the key is released.
11. Maintain per-frame previous-state snapshot to support pressed/released.
12. Expose keyboard API through the umbrella header.

## Group 3 — Mouse Polling

13. Implement `Rivet::GetMousePosition()` — returns `glm::vec2` cursor position.
14. Implement `Rivet::GetMouseDelta()` — returns frame-over-frame cursor delta.
15. Declare `enum class MouseButton` (Left, Right, Middle).
16. Implement `Rivet::IsMouseButtonDown(MouseButton btn)`.
17. Implement `Rivet::IsMouseButtonPressed(MouseButton btn)`.
18. Implement `Rivet::IsMouseButtonReleased(MouseButton btn)`.
19. Expose mouse API through the umbrella header.

## Group 4 — Window Resize Callback

20. Register a GLFW framebuffer-size callback inside `Window`.
21. Update the OpenGL viewport (`glViewport`) automatically on resize.
22. Expose `Rivet::GetWindowSize()` returning the current `glm::ivec2` dimensions.
23. Verify resize does not crash and viewport is correct after resize.

## Group 5 — Logging Macros

24. Create `Rivet/Source/Rivet/Logger.h` — initialise a named spdlog logger (`RVT_CORE_LOGGER`)
    and expose `RVT_CORE_INFO(...)` / `RVT_CORE_ERROR(...)` macros for internal engine use.
25. Create `Rivet/Source/Rivet/Logger.h` client section — expose `RVT_INFO(...)` / `RVT_ERROR(...)`
    macros backed by a separate `RVT_CLIENT_LOGGER` for Sandbox / game code.
26. Add a `Rivet::Log::Init()` call inside `Rivet::Init()` to spin up both loggers.
27. Replace any raw `spdlog::` calls in existing engine code with the internal macros.
28. Update Sandbox `Main.cpp` to use `RVT_INFO` / `RVT_ERROR` instead of raw spdlog.
29. Expose `Logger.h` through the umbrella header so client code only needs `#include <Rivet/Rivet.h>`.
