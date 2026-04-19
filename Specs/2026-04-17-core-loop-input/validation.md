# Phase 2 — Core Loop & Input: Validation

## Merge Criteria

All of the following must be true before this branch is merged into `main`.

---

### 1. Build

- [x] `cmake --build build` completes with zero errors and zero warnings on the target platform
      (Linux / Wayland).
- [x] The precompiled header (`Rvtph.h`) is not broken by any new include.

---

### 2. Application Lifecycle

- [x] `Sandbox` starts, opens a window, and runs the loop without crashing.
- [x] `spdlog` logs a frame counter to stdout that increments each frame (visible in terminal).
- [x] Closing the window (× button or Alt+F4) causes `ShouldClose()` to return true and the
      program exits cleanly (no hang, no assert).
- [x] `Shutdown()` is called exactly once at exit; no GLFW errors are printed.

---

### 3. Keyboard Polling

- [x] Holding a key (e.g. `W`) logs "W down" every frame via spdlog in Sandbox.
- [x] `IsKeyPressed` fires for exactly one frame on key-down — verified by a frame-count log
      message that does not repeat.
- [x] `IsKeyReleased` fires for exactly one frame on key-up — same verification method.
- [x] `IsKeyDown`, `IsKeyPressed`, and `IsKeyReleased` all return `false` for a key that is
      not being interacted with.

---

### 4. Mouse Polling

- [x] `GetMousePosition()` returns values that change as the cursor moves inside the window.
- [x] `GetMouseDelta()` returns `{0, 0}` when the cursor is stationary for a full frame.
- [x] `IsMouseButtonDown(MouseButton::Left)` returns true while LMB is held; logged in Sandbox.
- [x] `IsMouseButtonPressed` and `IsMouseButtonReleased` follow the same single-frame rules
      as their keyboard equivalents.

---

### 5. Window Resize

- [x] Resizing the window (drag edge) does not crash.
- [x] After resize, `GetWindowSize()` returns the new dimensions.
- [x] A coloured clear does not show black bars or distortion after resize, confirming
      `glViewport` was updated correctly.

---

### 6. Logging Macros

- [x] `RVT_CORE_INFO` and `RVT_CORE_ERROR` compile and produce tagged output (`[RIVET]` prefix)
      when called from inside the engine.
- [x] `RVT_INFO` and `RVT_ERROR` compile and produce tagged output (`[APP]` prefix) when called
      from Sandbox.
- [x] Both loggers are initialised before any macro is called (i.e. inside `Rivet::Init()`).
- [x] No raw `spdlog::` call remains in engine source files.
- [x] In a build with `NDEBUG` defined, all four macros expand to nothing (no log output, no
      runtime cost).

---

### 7. Code Quality

- [x] No new public symbol is missing from `Rivet/Rivet.h`.
- [x] No raw GLFW types or constants leak into public headers (users see only Rivet types).
- [x] All new source files are listed in the appropriate `CMakeLists.txt`.
- [x] Phase 2 items in `Specs/roadmap.md` are checked off.
