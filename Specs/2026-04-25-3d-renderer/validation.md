# Phase 13 — 3D Renderer: Validation

## Build
- [ ] `cmake --build build` completes with zero errors and zero new warnings
- [ ] Clean build from scratch (`rm -rf build && cmake … && make`) also passes

## 2D regression
- [ ] `RunScene2D()` launches, renders the 2D sprite scene, and closes without crash
- [ ] ImGui demo panel renders correctly in the 2D scene
- [ ] Audio playback and physics simulation behave identically to the Phase 12 baseline
- [ ] No existing `#include` paths broken by the addition of new files

## 3D scene correctness
- [ ] `RunScene3D()` opens a window and renders a textured cube using `basic3d.vert/frag`
- [ ] Cube rotates visibly each frame (model matrix updated per-frame)
- [ ] Checker texture is applied correctly to all cube faces (no stretched or missing UVs)
- [ ] Orbit camera responds to mouse drag: holding left button and dragging rotates the view around the cube
- [ ] Scroll wheel zooms the orbit radius in and out
- [ ] When two opaque 3D objects overlap in screen space, depth testing correctly occludes the further one (no z-fighting or see-through artefacts)
- [ ] FPS label in the UI overlay displays a non-zero, plausible frame rate

## OBJ loader
- [ ] `Rivet::LoadOBJ` successfully parses at least one external `.obj` file and returns a renderable `Mesh`
- [ ] The loader handles quad faces (triangulates them) without crashing

## Code hygiene
- [ ] `Renderer/3D/Camera3D.h`, `Mesh.h`, `ObjLoader.h` are reachable via `#include <Rivet/Rivet.h>`
- [ ] No raw GL calls in `Mesh::Draw()` that bypass the existing `Buffer`/`BufferLayout` abstractions (except the `glDrawElements` call itself)

## Merge criteria
All of the above pass on a clean build from scratch on the development machine.
