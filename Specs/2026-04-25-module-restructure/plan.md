# Phase 12 — Module Restructure: Plan

## 1. Reorganise Renderer source
- Create `Rivet/Source/Rivet/Renderer/Common/`, `Renderer/2D/`, `Renderer/3D/`
- Move `Shader`, `Buffer`, `BufferLayout`, `Texture` into `Renderer/Common/`
- Move `Renderer2D` → `Renderer/2D/Renderer.h/.cpp`, `Camera2D` → `Renderer/2D/Camera.h/.cpp`
- Drop the `2D` suffix from file names; folder path provides that context

## 2. Reorganise Physics source
- Create `Rivet/Source/Rivet/Physics/2D/` and `Physics/3D/`
- Move `Physics.h/.cpp`, `PhysicsTypes.h` into `Physics/2D/`, renaming to `Physics.h/.cpp`, `PhysicsTypes.h`

## 3. Reorganise Core source
- Create `Rivet/Source/Rivet/Core/`
- Move `App`, `Window`, `Input`, `Logger`, `Editor`, `Events/`, `Assets/`, `Audio/`, `UI/`, `Math/` into `Core/`

## 4. Update all internal includes
- Fix `#include` paths in every moved file to reflect new relative locations
- Update `Rvtph.h` (PCH) if it includes any of these files directly

## 5. Update CMakeLists
- Update `Rivet/CMakeLists.txt` glob/source lists to point to the new paths

## 6. Update umbrella header
- Rewrite `Rivet/Rivet.h` to include from the new module paths

## 7. Verify build and runtime
- Full clean build with no warnings introduced by the move
- Run Sandbox; confirm identical visual and behavioural output
