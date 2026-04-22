# Phase 8 — Asset Manager: Validation

The implementation is considered complete and ready to merge when **all** of the following are true.

## Functional Checks

- [ ] **Texture via manager** — Sandbox loads a texture exclusively through `Rvt::LoadTexture(path)`. No direct `stb_image` calls remain in Sandbox or game code.
- [ ] **Shader via manager** — Sandbox loads its shader exclusively through `Rvt::LoadShader(vertPath, fragPath)`. No direct `Shader(...)` constructor calls remain in Sandbox.
- [ ] **Cache hit** — Calling `Rvt::LoadTexture` (or `LoadShader`) twice with the same path returns the exact same cached object (verified by pointer equality or a log message confirming "cache hit").

## Structural Checks

- [ ] All asset manager source lives under `Rivet/Source/Rivet/Assets/`.
- [ ] Public headers are included via the umbrella `Rivet/Rivet.h`.
- [ ] No new external dependencies introduced.

## Build & Runtime Checks

- [ ] Project compiles without warnings on the existing CMake configuration.
- [ ] Sandbox runs, renders correctly, and shows no regressions vs. Phase 7 (textured quad, camera, ImGui overlay).
- [ ] `UnloadAll()` can be called at shutdown without crash or leak (verified via spdlog shutdown log or Valgrind clean run).
