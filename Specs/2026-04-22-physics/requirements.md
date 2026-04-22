# Phase 9 — Physics: Requirements

## Scope

Integrate a 2D physics subsystem into Rivet using Box2D as the backend. Expose a thin, free-function API consistent with Rivet's procedural style. Sandbox code should never include Box2D headers directly.

## Decisions

| Decision | Choice | Rationale |
|---|---|---|
| Physics backend | Box2D (via FetchContent) | Correctness complexity not worth hand-rolling; Box2D is lightweight and well-proven |
| API style | Free functions under `Rivet::Physics::` | Consistent with Rivet's raylib-style procedural philosophy |
| Type exposure | Opaque handles; no Box2D types in public headers | Keeps users decoupled from the backend |
| Scope | 2D only | Matches Rivet's mission |

## Public API Surface

```cpp
namespace Rivet::Physics {
    void Init();
    void Shutdown();
    void Step(float deltaTime);

    // Body creation
    BodyHandle AddStaticBody(glm::vec2 position, glm::vec2 halfExtents);
    BodyHandle AddDynamicBody(glm::vec2 position, glm::vec2 halfExtents, float density = 1.0f);

    // Query
    glm::vec2 GetPosition(BodyHandle handle);
    float     GetAngle(BodyHandle handle);

    // Manipulation
    void SetLinearVelocity(BodyHandle handle, glm::vec2 velocity);
    void ApplyImpulse(BodyHandle handle, glm::vec2 impulse);
}
```

## Context

- Box2D will be fetched via `FetchContent` in `Dependencies.cmake`, matching how other deps are managed.
- `BodyHandle` is a plain integer or small struct — no Box2D symbols leak through.
- `Step` is called once per application update tick with the frame delta time.
- Gravity is configurable at `Init` time (default: `{0, -9.8f}`).

## Out of Scope

- 3D physics
- Joints / constraints (future phase)
- Continuous collision detection (CCD)
- Sensors / triggers (future phase)
