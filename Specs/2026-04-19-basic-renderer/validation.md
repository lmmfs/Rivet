# Phase 4 — Basic Renderer: Validation

## Merge Criteria

All of the following must be true before this branch is merged into `main`.

---

### 1. Build

- [x] `cmake --build build` completes with zero errors and zero warnings on the target
      platform (Linux / Wayland).
- [x] The precompiled header (`Rvtph.h`) is not broken by any new include.
- [x] `Sandbox` compiles including only `<Rivet/Rivet.h>` — no direct `<glad/gl.h>` or
      GLM headers required in `Main.cpp`.
- [x] Sandbox shaders are present in the binary output directory after a build
      (`build/Sandbox/shaders/basic.vert` and `basic.frag` exist).

---

### 2. Shader System

- [x] `LoadShader` with valid paths returns a non-zero handle.
- [x] `LoadShader` with a missing or malformed GLSL file returns `0` and logs an
      spdlog error containing the file path and the GL error info string.
- [x] `UseShader(0)` does not crash (no-op or graceful guard).
- [x] Each uniform setter (`SetUniformInt`, `SetUniformFloat`, `SetUniformVec2/3/4`,
      `SetUniformMat4`) updates the value visible in the shader without GL errors
      (verified by the rendered output changing when the uniform changes).
- [x] `DeleteShader` releases the GL program without error (verified by running under
      a GL debug context or checking `glGetError`).

---

### 3. Buffer Abstractions

- [x] `CreateVertexBuffer` returns a non-zero handle and uploads data without GL errors.
- [x] `CreateIndexBuffer` returns a non-zero handle and uploads data without GL errors.
- [x] `CreateVertexArray` returns a non-zero handle.
- [x] `SetVertexAttrib` configures the layout correctly — the triangle renders with the
      expected vertex positions (not garbled geometry).
- [x] Delete functions release GL objects without error.

---

### 4. Renderer State

- [x] `SetClearColor(r, g, b, a)` followed by `Clear()` fills the window with the
      specified color (visually confirmed).
- [x] `SetViewport` resizes the rendering area as expected.
- [x] Resizing the window updates the viewport automatically — the triangle scales
      with the window and does not clip or show black bars from a stale viewport.

---

### 5. Sandbox Demo

- [x] Sandbox renders a visible, solid-color triangle in the center of the window
      at 60 fps (vsync) without tearing or flicker.
- [x] The `u_Color` uniform is set each frame; changing its value in source and
      rebuilding changes the triangle color.
- [x] The event queue from Phase 3 continues to work alongside rendering —
      key/mouse events are logged while the triangle is visible.
- [x] `RVT_INFO("FPS: {}", ...)` is printed to the console once per second;
      the reported value matches the expected vsync rate (~60).
- [x] Closing the window exits cleanly with no GL errors or crashes.

---

### 6. Regression

- [x] Phase 2 polling API (`IsKeyDown`, `GetMousePosition`, `GetWindowSize`) still
      compiles and returns correct values alongside the renderer.
- [x] Phase 3 event queue (`PollEvent`) still works correctly — no events are dropped
      or duplicated by the addition of the resize→viewport wiring.
- [x] `glGetError` returns `GL_NO_ERROR` at the end of each frame in the Sandbox demo.
