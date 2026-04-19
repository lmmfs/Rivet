# Phase 6 — GUI (Dear ImGui) · Validation

## Ready to Merge When

### Build
- [ ] Project configures and builds without errors on Linux / Wayland
- [ ] No new compiler warnings introduced by ImGui or the Editor wrapper
- [ ] `Rivet` static library links ImGui backends correctly

### Runtime
- [ ] Sandbox launches and the ImGui demo window renders visibly on screen
- [ ] Demo window is interactive (mouse, keyboard respond inside ImGui)
- [ ] No OpenGL errors logged during a normal run-and-close cycle

### Lifecycle
- [ ] Clean shutdown: no crash or assertion on `Editor::Shutdown` → `glfwDestroyWindow`
- [ ] No memory leaks reported by the process exit (valgrind or ASAN clean)

### API
- [ ] `Rivet::Editor::Init`, `Shutdown`, `Begin`, `End` are all declared in `Rivet/Editor.h`
- [ ] `Editor.h` is reachable via the umbrella header `Rivet/Rivet.h`
- [ ] Sandbox usage is explicit — no ImGui ticking happens unless `Begin`/`End` are called
