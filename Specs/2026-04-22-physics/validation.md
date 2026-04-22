# Phase 9 — Physics: Validation

## Build

- [ ] `cmake --build build` succeeds after adding Box2D — zero errors, zero new warnings.
- [ ] Box2D headers are not visible in `Sandbox/` includes (no `box2d/` includes in Sandbox source).

## Init / Shutdown

- [ ] Calling `Rivet::Physics::Init()` followed by `Rivet::Physics::Shutdown()` in Sandbox completes without crash or sanitizer error.
- [ ] Calling `Init` twice without `Shutdown` in between logs an error and does not double-allocate.

## Body Management

- [ ] `AddStaticBody` returns a valid (non-null) `BodyHandle`.
- [ ] `AddDynamicBody` returns a valid (non-null) `BodyHandle`, distinct from the static one.
- [ ] `GetPosition` on a newly created body returns the position it was created at (before any `Step`).

## Simulation

- [ ] After 60 calls to `Step(1/60.f)`, a dynamic body created at `{0, 5}` has a Y position less than 5 (gravity pulled it down).
- [ ] A dynamic body placed directly on a static ground body comes to rest within ~3 seconds of simulation time (no sinking, no tunneling).

## Sandbox Visual Demo

- [ ] Two colored quads (dynamic boxes) are drawn at their physics positions each frame.
- [ ] Both boxes visibly fall under gravity and land on the static ground quad.
- [ ] After landing, boxes remain on the ground (no slow sinking through the floor).
- [ ] Frame rate remains ≥ 60 FPS with the physics step active (no performance regression).

## Merge Criteria

All checkboxes above must be ticked. The `feat/physics` branch must rebase cleanly onto `main` before merge.
