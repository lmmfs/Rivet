# Phase 7 — 2D Drawing: Validation

## Acceptance Criteria

### Functional

- [ ] A PNG texture loads without errors; `Texture2D.id` is non-zero.
- [ ] Multiple sprites sharing the same texture are rendered in a single draw call (verify via draw call counter or RenderDoc).
- [ ] Sprites appear at the correct screen positions with correct aspect ratio.
- [ ] Camera pan (WASD) moves all sprites uniformly.
- [ ] Camera zoom (Q/E) scales the visible world around the origin.
- [ ] Reset (R) returns the camera to its initial state.
- [ ] ImGui overlay shows live camera position and zoom values.

### Correctness

- [ ] No OpenGL errors (`GL_NO_ERROR`) during a full frame with sprites rendered.
- [ ] `UnloadTexture` releases the GPU resource (no leak reported by a GPU debug layer).
- [ ] `Renderer2DShutdown` frees all batch buffers without crash.

### Build & Integration

- [ ] Project compiles cleanly (`make -j$(nproc)`) with no new warnings.
- [ ] Sandbox runs to a stable frame loop; no crash on close.
- [ ] Phase 7 items are checked off in `Specs/roadmap.md`.

## Manual Test Procedure

1. Build: `cd build && make -j$(nproc)`.
2. Run: `./Sandbox/Sandbox`.
3. Confirm sprites (≥ 3) are visible from the same texture sheet.
4. Pan the camera with WASD — sprites should scroll.
5. Zoom with Q/E — world should scale.
6. Press R — camera resets to default.
7. Inspect the ImGui overlay for live camera data.
8. Close the window — no crash, no leak warnings in terminal.
