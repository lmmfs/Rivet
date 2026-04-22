# Phase 7 — 2D Drawing: Plan

## Task Group 1 — Texture Loading

1.1 Add a `Texture2D` struct to `Rivet/Renderer/Texture.h` (id, width, height, channels).  
1.2 Implement `Texture2D LoadTexture(const std::string& path)` using stb_image (RGBA forced).  
1.3 Implement `void UnloadTexture(Texture2D& tex)` — calls `glDeleteTextures`.  
1.4 Expose both in the umbrella header `Rivet/Rivet.h`.  
1.5 Add a test PNG asset to `Sandbox/assets/` for use in the demo.

## Task Group 2 — Orthographic Camera

2.1 Add a `Camera2D` struct (position `glm::vec2`, zoom `float`, rotation `float`).  
2.2 Implement `glm::mat4 GetCamera2DMatrix(const Camera2D& cam)` using `glm::ortho` + view transform.  
2.3 Implement `void BeginCamera2D(const Camera2D& cam)` / `void EndCamera2D()` — push/pop view-projection.  
2.4 Store the active VP matrix in a small internal Renderer2D state struct.

## Task Group 3 — Quad Batch Renderer

3.1 Create `Rivet/Renderer/Renderer2D.h/.cpp` with internal batch state (VBO, VAO, index buffer, shader, texture slot).  
3.2 Write the batch vertex/fragment shaders (`quad.vert`, `quad.frag`) supporting position, UV, tint, and texture sampler.  
3.3 Implement `void Renderer2DInit()` / `void Renderer2DShutdown()`.  
3.4 Implement `void BeginScene()` / `void EndScene()` — resets batch, flushes on `EndScene`.  
3.5 Implement `void Flush()` — uploads vertex data, binds texture, issues `glDrawElements`, resets counters.  
3.6 Implement `void DrawTexture(const Texture2D& tex, glm::vec2 pos, glm::vec2 size, glm::vec4 tint)`.  
3.7 Trigger `Flush()` automatically when the batch is full or a new texture is used.

## Task Group 4 — Sandbox Demo

4.1 Load a PNG texture on startup using `LoadTexture`.  
4.2 Create a `Camera2D` and render multiple sprites (same texture) per frame.  
4.3 Add keyboard controls: WASD to pan, Q/E to zoom, R to reset camera.  
4.4 Display camera position and zoom via an ImGui overlay.  
4.5 Call `UnloadTexture` and `Renderer2DShutdown` on exit.

## Task Group 5 — Cleanup & Roadmap Update

5.1 Verify no OpenGL errors (`glGetError`) remain in the hot path.  
5.2 Mark Phase 7 items as done in `Specs/roadmap.md`.  
5.3 Update umbrella header and PCH if needed.
