# Phase 12 — Module Restructure: Validation

## Build
- [ ] `cmake --build build` completes with zero errors and zero new warnings
- [ ] `compile_commands.json` reflects the new include paths (spot-check a moved header)

## Runtime
- [ ] Sandbox launches without crash
- [ ] Window opens, renders, and closes identically to the pre-restructure baseline
- [ ] ImGui demo panel renders correctly
- [ ] Audio playback works if triggered in Sandbox
- [ ] Physics simulation (if exercised in Sandbox) behaves identically

## Code hygiene
- [ ] No `#include` paths in the codebase still point to the old locations
- [ ] No duplicate or orphaned files left in the old directories
- [ ] `Rivet/Rivet.h` umbrella header compiles cleanly in isolation (include it in a scratch `.cpp` with no other includes)

## Merge criteria
All of the above pass on a clean build from scratch (`rm -rf build && cmake … && make`).
