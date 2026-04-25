# Phase 13 — 3D Renderer: Requirements

## Scope
Introduce the 3D renderer module into the pre-existing `Renderer/3D/` skeleton: a perspective camera with an orbit controller, a mesh abstraction backed by a hand-rolled OBJ loader, and a textured 3D draw call. The existing 2D path must remain fully functional.

## Motivation
The module restructure in Phase 12 created `Renderer/3D/` and `Physics/3D/` as empty placeholders. Phase 13 populates the renderer half so that Phases 14–15 can add 3D physics and compose a full 3D scene.

## Decisions

### Camera
- **Projection:** perspective only (`glm::perspective`). Orthographic 3D is out of scope.
- **Controller style:** orbit (arcball-ish) — drag rotates yaw/pitch around a fixed target; scroll wheel adjusts radius. No fly-cam.
- **Input wiring:** uses the existing `Rivet::Input` polling API (mouse delta, scroll).

### Mesh & geometry
- **Mesh format:** indexed triangle list; each vertex carries `vec3 position`, `vec3 normal`, `vec2 uv`.
- **Buffer reuse:** `Mesh` internally creates a `Rivet::Buffer` (VBO) and an index buffer using the existing `Renderer/Common/` types; it also sets up the `BufferLayout`.
- **Hardcoded cube:** a unit cube defined in code (no OBJ file needed for the Sandbox demo) is the minimum required for validation. The OBJ loader is required but can be validated with any OBJ file.

### OBJ loader
- Hand-rolled; parses `v`, `vn`, `vt`, `f` tokens only.
- Triangulates quad faces (`f` lines with 4 vertices).
- Indexed output: deduplicates unique `(pos/uv/normal)` triplets.
- Does **not** support materials, groups, or multi-object files in this phase.

### Texture
- Reuse `Rivet::Texture2D` from `Renderer/Common/Texture.h`. No new texture type needed.
- The spinning cube demo reuses the existing `assets/checker.png`.

### Shaders
- New GLSL files in `Sandbox/shaders/`: `basic3d.vert` / `basic3d.frag`.
- Uniforms: `u_Model` (mat4), `u_View` (mat4), `u_Projection` (mat4), `u_Texture` (sampler2D).

### Depth testing
- `glEnable(GL_DEPTH_TEST)` called once at init (inside `Renderer3D::Init` or `Rivet::Init`).
- `GL_DEPTH_BUFFER_BIT` added to the `glClear` call each frame.
- The 2D renderer is unaffected (it disables depth testing for its draw calls).

### Sandbox isolation
- Existing `Main.cpp` logic is extracted into `Scene2D.cpp`/`RunScene2D()` before any 3D code is added. This prevents the file growing unmanageable and makes it easy to switch scenes.

## Out of scope
- Lighting (Phong, normals-based shading) — deferred to a future phase
- Shadow mapping
- Instanced rendering
- Multiple meshes in one draw call
- 3D physics (Phase 14)
- Multi-object or multi-material OBJ files

## Key types introduced

| Symbol | Header | Notes |
|---|---|---|
| `Rivet::Camera3D` | `Renderer/3D/Camera3D.h` | Perspective + orbit |
| `Rivet::Mesh` | `Renderer/3D/Mesh.h` | Vertex/index buffers, Draw() |
| `Rivet::LoadOBJ` | `Renderer/3D/ObjLoader.h` | Returns `Mesh` |
