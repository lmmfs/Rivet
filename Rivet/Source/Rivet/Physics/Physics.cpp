#include "Physics.h"

#include <box2d/box2d.h>
#include <spdlog/spdlog.h>

#include <unordered_map>

namespace Rivet::Physics {

// ---------------------------------------------------------------------------
// Internal state
// ---------------------------------------------------------------------------

struct State
{
    b2World*                          world    = nullptr;
    std::unordered_map<int32_t, b2Body*> bodies;
    int32_t                           nextId   = 0;
};

static State s_State;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static b2Body* FindBody(BodyHandle handle)
{
    auto it = s_State.bodies.find(handle.id);
    if (it == s_State.bodies.end()) return nullptr;
    return it->second;
}

// ---------------------------------------------------------------------------
// Init / Shutdown
// ---------------------------------------------------------------------------

void Init(glm::vec2 gravity)
{
    if (s_State.world)
    {
        spdlog::error("[Physics] Init called while already initialised — ignored");
        return;
    }

    b2Vec2 g{ gravity.x, gravity.y };
    s_State.world  = new b2World(g);
    s_State.nextId = 0;
    s_State.bodies.clear();

    spdlog::info("[Physics] Initialised (gravity {:.2f}, {:.2f})", gravity.x, gravity.y);
}

void Shutdown()
{
    if (!s_State.world) return;

    delete s_State.world;
    s_State.world = nullptr;
    s_State.bodies.clear();
    s_State.nextId = 0;

    spdlog::info("[Physics] Shutdown");
}

// ---------------------------------------------------------------------------
// Simulation
// ---------------------------------------------------------------------------

void Step(float deltaTime)
{
    if (!s_State.world) return;

    constexpr int32 velocityIterations = 8;
    constexpr int32 positionIterations = 3;
    s_State.world->Step(deltaTime, velocityIterations, positionIterations);
}

// ---------------------------------------------------------------------------
// Body creation
// ---------------------------------------------------------------------------

BodyHandle AddStaticBody(glm::vec2 position, glm::vec2 halfExtents)
{
    if (!s_State.world)
    {
        spdlog::error("[Physics] AddStaticBody called before Init");
        return {};
    }

    b2BodyDef bodyDef;
    bodyDef.type     = b2_staticBody;
    bodyDef.position = { position.x, position.y };

    b2Body* body = s_State.world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(halfExtents.x, halfExtents.y);
    body->CreateFixture(&shape, 0.0f);

    BodyHandle handle{ s_State.nextId++ };
    s_State.bodies[handle.id] = body;
    return handle;
}

BodyHandle AddDynamicBody(glm::vec2 position, glm::vec2 halfExtents, float density)
{
    if (!s_State.world)
    {
        spdlog::error("[Physics] AddDynamicBody called before Init");
        return {};
    }

    b2BodyDef bodyDef;
    bodyDef.type     = b2_dynamicBody;
    bodyDef.position = { position.x, position.y };

    b2Body* body = s_State.world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(halfExtents.x, halfExtents.y);

    b2FixtureDef fixtureDef;
    fixtureDef.shape       = &shape;
    fixtureDef.density     = density;
    fixtureDef.friction    = 0.3f;
    fixtureDef.restitution = 0.4f;
    body->CreateFixture(&fixtureDef);

    BodyHandle handle{ s_State.nextId++ };
    s_State.bodies[handle.id] = body;
    return handle;
}

// ---------------------------------------------------------------------------
// Query
// ---------------------------------------------------------------------------

glm::vec2 GetPosition(BodyHandle handle)
{
    b2Body* body = FindBody(handle);
    if (!body) return {};
    const b2Vec2& pos = body->GetPosition();
    return { pos.x, pos.y };
}

float GetAngle(BodyHandle handle)
{
    b2Body* body = FindBody(handle);
    if (!body) return 0.0f;
    return body->GetAngle();
}

// ---------------------------------------------------------------------------
// Manipulation
// ---------------------------------------------------------------------------

void SetLinearVelocity(BodyHandle handle, glm::vec2 velocity)
{
    b2Body* body = FindBody(handle);
    if (!body) return;
    body->SetLinearVelocity({ velocity.x, velocity.y });
}

void ApplyImpulse(BodyHandle handle, glm::vec2 impulse)
{
    b2Body* body = FindBody(handle);
    if (!body) return;
    body->ApplyLinearImpulseToCenter({ impulse.x, impulse.y }, true);
}

} // namespace Rivet::Physics
