# Phase 6 — GUI (Dear ImGui) · Plan

## 1. ImGui Dependency Integration
- Add Dear ImGui (docking branch) via CMake FetchContent in `Dependencies.cmake`
- Include GLFW + OpenGL3 backends from the ImGui source tree
- Link ImGui into the Rivet static library target
- Verify Sandbox builds cleanly with no new warnings

## 2. Editor Wrapper — Init & Shutdown
- Create `Rivet/Editor.h` / `Editor.cpp` under `Rivet/Source/Rivet/`
- Expose `Rivet::Editor::Init(GLFWwindow*)` — calls `ImGui::CreateContext`, configures IO flags (docking, viewports), installs GLFW + OpenGL3 backends
- Expose `Rivet::Editor::Shutdown()` — calls backend shutdown and `ImGui::DestroyContext`
- Add `Editor.h` to the umbrella header `Rivet/Rivet.h`

## 3. Per-Frame Begin / End
- Expose `Rivet::Editor::Begin()` — calls `ImGui_ImplOpenGL3_NewFrame`, `ImGui_ImplGlfw_NewFrame`, `ImGui::NewFrame`
- Expose `Rivet::Editor::End()` — calls `ImGui::Render`, `ImGui_ImplOpenGL3_RenderDrawData`; handles viewport platform windows if enabled

## 4. Sandbox Integration — ImGui Demo
- In `Sandbox/Source/Main.cpp`, call `Editor::Init` after window creation
- In the main loop, call `Editor::Begin`, show `ImGui::ShowDemoWindow`, then `Editor::End`
- Call `Editor::Shutdown` before window destruction
