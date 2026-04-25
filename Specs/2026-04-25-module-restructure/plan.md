# Phase 12 — Module Restructure: Plan

## 1. Reorganise Renderer source ✅
- Created `Rivet/Source/Rivet/Renderer/Common/`, `Renderer/2D/`, `Renderer/3D/`
- Moved `Shader`, `Buffer`, `BufferLayout`, `Texture` into `Renderer/Common/`
- Moved `Renderer2D` → `Renderer/2D/Renderer.h/.cpp`, `Camera2D` → `Renderer/2D/Camera.h/.cpp`
- Dropped the `2D` suffix from file names; folder path provides that context

## 2. Reorganise Physics source ✅
- Created `Rivet/Source/Rivet/Physics/2D/` and `Physics/3D/`
- Moved `Physics.h/.cpp`, `PhysicsTypes.h` into `Physics/2D/`

## 3. Reorganise Core source ✅
- Created `Rivet/Source/Rivet/Core/`
- Moved `App`, `Window`, `Input`, `Logger`, `Editor`, `Events/`, `Assets/`, `Audio/`, `UI/`, `Math/` into `Core/`

## 4. Update all internal includes ✅
- Fixed `Renderer/Common/Shader.cpp`: `../Logger.h` → `../../Core/Logger.h`
- Fixed `Renderer/2D/Renderer.h`: `Texture.h` → `../Common/Texture.h`
- Fixed `Renderer/2D/Renderer.cpp`: `Renderer2D.h` → `Renderer.h`, `Shader.h` → `../Common/Shader.h`
- Fixed `Renderer/2D/Camera.cpp`: names + `../App.h` → `../../Core/App.h`
- Fixed `Core/Assets/TextureManager.h`: `../Renderer/Texture.h` → `../../Renderer/Common/Texture.h`
- Fixed `Core/Assets/ShaderManager.h`: `../Renderer/Shader.h` → `../../Renderer/Common/Shader.h`
- Fixed `Core/UI/UI.cpp`: `../Renderer/Renderer2D.h` → `../../Renderer/2D/Renderer.h`, `../Renderer/Texture.h` → `../../Renderer/Common/Texture.h`

## 5. Update CMakeLists ✅
- Updated `Rivet/CMakeLists.txt` source list to all new paths, with section comments

## 6. Update umbrella header ✅
- Rewrote `Rivet/Rivet.h` to include from the new module paths

## 7. Verify build and runtime ✅
- Full clean incremental build: zero errors, zero new warnings
- `libRivet.a` and `Sandbox` executable built successfully
