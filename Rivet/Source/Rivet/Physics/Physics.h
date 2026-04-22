#pragma once

#include "PhysicsTypes.h"

#include <glm/glm.hpp>

namespace Rivet::Physics {

    // Initialise the physics world. Safe to call once per app session.
    void Init(glm::vec2 gravity = { 0.0f, -9.8f });

    // Tear down the physics world and free all bodies.
    void Shutdown();

    // Advance the simulation by deltaTime seconds.
    void Step(float deltaTime);

    // Body creation — returns an opaque handle valid until Shutdown().
    BodyHandle AddStaticBody (glm::vec2 position, glm::vec2 halfExtents);
    BodyHandle AddDynamicBody(glm::vec2 position, glm::vec2 halfExtents,
                              float density = 1.0f);

    // Query — returns world-space position / orientation.
    glm::vec2 GetPosition(BodyHandle handle);
    float     GetAngle   (BodyHandle handle);   // radians

    // Manipulation
    void SetLinearVelocity(BodyHandle handle, glm::vec2 velocity);
    void ApplyImpulse     (BodyHandle handle, glm::vec2 impulse);

} // namespace Rivet::Physics
