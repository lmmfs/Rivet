# Phase 9 — Physics: Plan

## Task Group 1 — Box2D Dependency

1.1 Add Box2D to `Dependencies.cmake` via `FetchContent` (tag a stable release).  
1.2 Link `box2d` to the `Rivet` static library target in `Rivet/CMakeLists.txt`.  
1.3 Confirm clean build with no changes to Sandbox.

---

## Task Group 2 — Physics Subsystem Headers

2.1 Create `Rivet/Source/Rivet/Physics/PhysicsTypes.h` — define `BodyHandle` (opaque integer wrapper) and `BodyType` enum (`Static`, `Dynamic`).  
2.2 Create `Rivet/Source/Rivet/Physics/Physics.h` — declare all public free functions under `Rivet::Physics::`.  
2.3 Add `#include "Rivet/Physics/Physics.h"` to the umbrella header `Rivet/Rivet.h`.

---

## Task Group 3 — Physics Init / Shutdown

3.1 Create `Rivet/Source/Rivet/Physics/Physics.cpp`.  
3.2 Implement `Init(glm::vec2 gravity = {0, -9.8f})` — construct `b2World`, store in internal state.  
3.3 Implement `Shutdown()` — destroy world, clear internal handle map.  
3.4 Verify Init/Shutdown cycle runs without crash in Sandbox.

---

## Task Group 4 — Body Creation & Query

4.1 Implement `AddStaticBody` — create a static `b2Body` with a box fixture, return a `BodyHandle`.  
4.2 Implement `AddDynamicBody` — create a dynamic `b2Body` with density, return a `BodyHandle`.  
4.3 Implement `GetPosition` and `GetAngle` — look up handle in map, return body transform data.  
4.4 Implement `SetLinearVelocity` and `ApplyImpulse`.

---

## Task Group 5 — Simulation Step

5.1 Implement `Step(float deltaTime)` — call `b2World::Step` with fixed velocity/position iterations (8/3).  
5.2 Wire `Rivet::Physics::Step(dt)` into the application loop in `Application.cpp` (after update, before render).

---

## Task Group 6 — Sandbox Demo

6.1 In `Sandbox/Source/Main.cpp`, call `Rivet::Physics::Init()` on startup and `Shutdown()` on exit.  
6.2 Create a static ground body and two dynamic box bodies above it.  
6.3 Each frame: call `Step`, retrieve positions, draw colored quads at the physics positions using existing renderer.  
6.4 Confirm visually: boxes fall, land on ground, and bounce/rest correctly.
