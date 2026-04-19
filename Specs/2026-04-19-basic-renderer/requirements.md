# Phase 4 — Basic Renderer: Requirements

## Scope

Introduce the minimal OpenGL rendering pipeline: shaders loaded from disk, buffer
objects (VAO/VBO/EBO) managed through opaque handles and free functions, and basic
renderer-state control (clear color, viewport). The deliverable is a Sandbox that
renders a solid-color triangle using the new API.

### In scope
- `Shader` handle + `LoadShader(vertPath, fragPath)` / `DeleteShader` / `UseShader`
- Uniform setters: `int`, `float`, `vec2`, `vec3`, `vec4`, `mat4`
- `VertexBuffer`, `IndexBuffer`, `VertexArray` opaque handles + create/delete/bind helpers
- `SetVertexAttrib` — configures `glVertexAttribPointer` layout
- `SetClearColor`, `Clear`, `SetViewport`
- Viewport auto-update wired into the window resize callback
- `Sandbox/shaders/` directory; CMake copies shaders to binary output dir at build time
- FPS logged to console once per second via `RVT_INFO` in Sandbox
- Full exposure through `Rivet/Rivet.h`

### Out of scope
- Inline shader source strings (file-path loading only)
- Uniform location caching / shader reflection
- Uniform Buffer Objects (UBOs)
- Geometry, compute, or tessellation shaders
- Instanced rendering
- Multiple render targets / framebuffers
- Depth/stencil buffer control (deferred)
- Draw-call batching (Phase 5)
- Texture loading and binding (Phase 5)

---

## API Style Decisions

**Opaque handles + free functions**  
All GPU objects (`Shader`, `VertexBuffer`, `IndexBuffer`, `VertexArray`) are `uint32_t`
typedefs — they wrap the underlying OpenGL name. Operations on them are free functions,
consistent with the procedural, raylib-style API Rivet targets.

```cpp
// Intended usage
Rivet::Shader shader = Rivet::LoadShader("shaders/basic.vert", "shaders/basic.frag");

float vertices[] = { -0.5f, -0.5f, 0.0f,
                      0.5f, -0.5f, 0.0f,
                      0.0f,  0.5f, 0.0f };

Rivet::VertexArray  va = Rivet::CreateVertexArray();
Rivet::VertexBuffer vb = Rivet::CreateVertexBuffer(vertices, sizeof(vertices));
Rivet::SetVertexAttrib(0, 3, 3 * sizeof(float), 0);  // attrib 0: vec3 position

Rivet::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);

while (Rivet::IsRunning()) {
    Rivet::BeginFrame();
    Rivet::Clear();
    Rivet::UseShader(shader);
    Rivet::SetUniformVec4(shader, "u_Color", { 1.0f, 0.5f, 0.2f, 1.0f });
    Rivet::BindVertexArray(va);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    Rivet::EndFrame();
}

Rivet::DeleteVertexArray(va);
Rivet::DeleteVertexBuffer(vb);
Rivet::DeleteShader(shader);
```

**Shader source from file paths**  
`LoadShader` accepts two file paths relative to the working directory. The engine reads
the files at call time. No inline source string overload in this phase.

**Shader errors are non-fatal**  
Compilation and link errors are logged via `spdlog` (error level). `LoadShader` returns
`0` (invalid handle) on failure. Callers are expected to check the return value.

**`SetVertexAttrib` is stateful**  
`SetVertexAttrib` must be called while the target VAO and VBO are bound; it does not
accept explicit handle parameters. This mirrors the underlying OpenGL state machine and
keeps the API minimal.

**Viewport tracks resize automatically**  
`Rivet::SetViewport` is called internally from the GLFW resize callback. Callers can also
call it explicitly to override (e.g., for split-screen viewports in the future).

---

## Context

This phase builds on Phase 3's event queue. The window resize event now has a second
consumer: the internal resize callback also calls `glViewport` so the triangle does not
deform when the window is resized.

The `Sandbox/shaders/` directory is Sandbox-only; Rivet itself ships no shaders. The CMake
copy step ensures shaders are available next to the `Sandbox` binary in the build tree
regardless of where CMake is invoked from.
