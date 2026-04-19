# Phase 4 — Basic Renderer: Plan

## Group 1 — Shader System

1. Define a `Shader` opaque handle (`uint32_t` typedef).
2. Implement `Rivet::LoadShader(const char* vertexPath, const char* fragmentPath)` —
   reads both GLSL files from disk, compiles each stage, links the program, returns
   a valid `Shader` handle on success.
3. Log per-stage compilation errors and link errors via `spdlog`; return a zero/invalid
   handle on failure so the caller can detect and handle it.
4. Implement `Rivet::DeleteShader(Shader shader)` — calls `glDeleteProgram`.
5. Implement `Rivet::UseShader(Shader shader)` — calls `glUseProgram`.
6. Implement uniform setters (resolve location by name each call):
   - `SetUniformInt(Shader, const char* name, int value)`
   - `SetUniformFloat(Shader, const char* name, float value)`
   - `SetUniformVec2(Shader, const char* name, glm::vec2)`
   - `SetUniformVec3(Shader, const char* name, glm::vec3)`
   - `SetUniformVec4(Shader, const char* name, glm::vec4)`
   - `SetUniformMat4(Shader, const char* name, const glm::mat4&)`
7. Expose all shader types and functions through `Rivet/Rivet.h`.

## Group 2 — Buffer Abstractions (VAO / VBO / EBO)

8. Define `VertexBuffer`, `IndexBuffer`, and `VertexArray` as `uint32_t` opaque handles.
9. Implement `Rivet::CreateVertexBuffer(const float* data, uint32_t size)` —
   generates and uploads to a `GL_ARRAY_BUFFER` with `GL_STATIC_DRAW`.
10. Implement `Rivet::DeleteVertexBuffer(VertexBuffer vb)`.
11. Implement `Rivet::CreateIndexBuffer(const uint32_t* data, uint32_t count)` —
    generates and uploads to a `GL_ELEMENT_ARRAY_BUFFER`.
12. Implement `Rivet::DeleteIndexBuffer(IndexBuffer ib)`.
13. Implement `Rivet::CreateVertexArray()` — generates and binds a VAO.
14. Implement `Rivet::DeleteVertexArray(VertexArray va)`.
15. Implement `Rivet::BindVertexArray(VertexArray va)` / `Rivet::BindVertexBuffer(VertexBuffer vb)` /
    `Rivet::BindIndexBuffer(IndexBuffer ib)`.
16. Implement `Rivet::SetVertexAttrib(uint32_t index, int size, uint32_t stride, uint32_t offset)` —
    calls `glVertexAttribPointer` + `glEnableVertexAttribArray`; must be called while the
    target VAO and VBO are bound.
17. Expose all buffer types and functions through `Rivet/Rivet.h`.

## Group 3 — Renderer State

18. Implement `Rivet::SetClearColor(float r, float g, float b, float a)`.
19. Implement `Rivet::Clear()` — calls `glClear(GL_COLOR_BUFFER_BIT)`.
20. Implement `Rivet::SetViewport(int x, int y, int width, int height)` —
    calls `glViewport`.
21. Wire `SetViewport(0, 0, width, height)` into the GLFW window resize callback so
    the viewport tracks window size automatically.
22. Expose renderer-state functions through `Rivet/Rivet.h`.

## Group 4 — Sandbox Shaders & Integration

23. Create `Sandbox/shaders/basic.vert` — minimal vertex shader passing position through.
24. Create `Sandbox/shaders/basic.frag` — minimal fragment shader outputting a solid color
    via a `vec4 u_Color` uniform.
25. Add a CMake `add_custom_command` / `add_custom_target` to `Sandbox/CMakeLists.txt` that
    copies `Sandbox/shaders/` to the Sandbox binary output directory at build time.
26. Update Sandbox `Main.cpp`:
    - Call `Rivet::SetClearColor` once at startup.
    - Load the shader via `Rivet::LoadShader("shaders/basic.vert", "shaders/basic.frag")`.
    - Create a VAO + VBO for a single triangle; set up one vertex attribute (position).
    - Each frame: `Rivet::Clear()`, `Rivet::UseShader(shader)`,
      set `u_Color` uniform, draw with `glDrawArrays`.
    - Track frame count and elapsed time via `glfwGetTime()`; log FPS once per second
      with `RVT_INFO("FPS: {}", fpsCount)`.
27. Verify `Main.cpp` still compiles with only `<Rivet/Rivet.h>` included.
