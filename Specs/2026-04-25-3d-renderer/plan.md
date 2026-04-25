# Phase 13 — 3D Renderer: Plan

## 1. Isolate current Sandbox into a 2D scene file
- Move all existing `Main.cpp` logic into `Sandbox/Source/Scene2D.cpp` (a free function `void RunScene2D()`)
- Replace `Main.cpp` with a minimal dispatcher that calls `RunScene2D()` or `RunScene3D()` via a compile-time or runtime flag
- Verify the 2D scene still compiles and runs identically after the move

## 2. 3D Camera
- Create `Rivet/Source/Rivet/Renderer/3D/Camera3D.h/.cpp`
- Perspective projection (`glm::perspective`, configurable FOV/near/far)
- Look-at view matrix (`glm::lookAt`)
- Orbit controller: yaw/pitch rotation around a target point driven by mouse drag; scroll wheel zoom

## 3. Mesh abstraction
- Create `Rivet/Source/Rivet/Renderer/3D/Mesh.h/.cpp`
- `Mesh` struct: vertex buffer (position `vec3`, normal `vec3`, UV `vec2`), index buffer, VAO
- `Mesh::Bind()` / `Mesh::Unbind()`, `Mesh::Draw()` (indexed draw call)
- Reuse `Buffer` and `BufferLayout` from `Renderer/Common/`

## 4. OBJ loader
- Create `Rivet/Source/Rivet/Renderer/3D/ObjLoader.h/.cpp`
- Hand-rolled parser: read `v`, `vn`, `vt`, `f` lines; triangulate quads
- Returns a `Mesh` ready to upload
- No external parsing library; stdlib only

## 5. 3D shaders and draw call
- Add `Sandbox/shaders/basic3d.vert` / `basic3d.frag`
  - Uniforms: `u_Model` (mat4), `u_View` (mat4), `u_Projection` (mat4), `u_Texture` (sampler2D)
  - Vertex attributes match the `Mesh` layout (position, normal, UV)
- Enable depth testing (`glEnable(GL_DEPTH_TEST)`) in `Rivet::Init` or a dedicated `Renderer3D::Init`
- Clear the depth buffer each frame alongside the colour buffer

## 6. 3D Sandbox scene
- Create `Sandbox/Source/Scene3D.cpp` with `void RunScene3D()`
- Load a cube OBJ (or generate a hardcoded unit cube) and a checker texture (reuse existing asset)
- Render a spinning textured cube: rotate model matrix each frame
- Attach the orbit camera to mouse input
- Display FPS via the existing UI overlay
- Update `Main.cpp` to call `RunScene3D()`

## 7. CMake & umbrella header updates
- Add new `.cpp` files to `Rivet/CMakeLists.txt` source list
- Add `Sandbox/Source/Scene2D.cpp`, `Scene3D.cpp` to `Sandbox/CMakeLists.txt`
- Expose `Camera3D`, `Mesh`, `ObjLoader` through `Rivet/Rivet.h`
