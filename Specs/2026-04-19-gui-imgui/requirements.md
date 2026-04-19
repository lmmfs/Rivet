# Phase 6 — GUI (Dear ImGui) · Requirements

## Scope

Integrate Dear ImGui into the Rivet engine and expose a thin, explicit wrapper (`Rivet::Editor`) that the Sandbox (or any future game) calls manually from its main loop.

## What's In
- Dear ImGui added as an engine dependency (linked into `Rivet` lib)
- `Rivet::Editor` namespace with `Init`, `Shutdown`, `Begin`, `End`
- Sandbox calls the wrapper explicitly — one demo window as proof of integration

## What's Out
- No automatic/hidden ImGui ticking inside the engine's app loop
- No custom widgets or Rivet-specific UI panels (deferred to a later editor phase)
- No docking layout persistence

## Key Decisions

| Decision | Choice | Rationale |
|---|---|---|
| ImGui version | docking branch | Already specified in tech-stack.md; enables future layout features |
| API style | Free functions inside `Rivet::Editor` namespace | Consistent with mission: procedural, raylib-style |
| Ownership | Engine (Rivet lib) owns the ImGui context | Keeps windowing/rendering details out of Sandbox |
| Caller responsibility | Sandbox explicitly calls `Begin`/`End` each frame | Makes the call site visible and intentional; no hidden magic |
| Backends | `imgui_impl_glfw` + `imgui_impl_opengl3` | Matches existing GLFW 3.4 / OpenGL 4.6 Core stack |

## Integration Points
- `Editor::Init` receives the `GLFWwindow*` from the existing `Window` class
- `Editor::Begin` / `End` must be called between `glClear` and `glfwSwapBuffers`
- `Editor::Shutdown` must be called before `glfwDestroyWindow`

## Constraints
- Must compile on Linux / Wayland (same target as Phase 1–5)
- No new compiler warnings introduced
- ImGui fetched at configure time via `FetchContent`; not vendored manually
