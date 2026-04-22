#include "Renderer2D.h"
#include "Shader.h"

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <spdlog/spdlog.h>

#include <array>
#include <vector>

namespace Rivet {
namespace Renderer2D {

// ---------------------------------------------------------------------------
// Batch constants
// ---------------------------------------------------------------------------

static constexpr uint32_t MaxQuads    = 1000;
static constexpr uint32_t MaxVertices = MaxQuads * 4;
static constexpr uint32_t MaxIndices  = MaxQuads * 6;

// Vertex layout: position(2) + uv(2) + tint(4) = 8 floats
struct QuadVertex
{
    float x, y;
    float u, v;
    float r, g, b, a;
};

// ---------------------------------------------------------------------------
// Internal state
// ---------------------------------------------------------------------------

struct State
{
    uint32_t vao         = 0;
    uint32_t vbo         = 0;   // GL_DYNAMIC_DRAW
    uint32_t ibo         = 0;   // GL_STATIC_DRAW
    Shader   shader      = 0;

    std::array<QuadVertex, MaxVertices> vertexBuffer{};
    uint32_t quadCount      = 0;
    uint32_t currentTexture = 0;

    glm::mat4 viewProj = glm::mat4(1.0f);
};

static State s_State;

// ---------------------------------------------------------------------------
// Init / Shutdown
// ---------------------------------------------------------------------------

void Init()
{
    // ---- VAO ---------------------------------------------------------------
    glGenVertexArrays(1, &s_State.vao);
    glBindVertexArray(s_State.vao);

    // ---- Dynamic VBO -------------------------------------------------------
    glGenBuffers(1, &s_State.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, s_State.vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(MaxVertices * sizeof(QuadVertex)),
                 nullptr, GL_DYNAMIC_DRAW);

    // Attrib 0 — position (vec2)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex),
                          reinterpret_cast<void*>(offsetof(QuadVertex, x)));
    // Attrib 1 — uv (vec2)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex),
                          reinterpret_cast<void*>(offsetof(QuadVertex, u)));
    // Attrib 2 — tint (vec4)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex),
                          reinterpret_cast<void*>(offsetof(QuadVertex, r)));

    // ---- Static IBO --------------------------------------------------------
    std::array<uint32_t, MaxIndices> indices{};
    uint32_t offset = 0;
    for (uint32_t i = 0; i < MaxIndices; i += 6, offset += 4)
    {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;
        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;
    }

    glGenBuffers(1, &s_State.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_State.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(MaxIndices * sizeof(uint32_t)),
                 indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

    // ---- Shader ------------------------------------------------------------
    s_State.shader = LoadShader("shaders/quad.vert", "shaders/quad.frag");
    if (!s_State.shader)
        spdlog::error("[Renderer2D] Failed to load quad shaders");

    // Bind texture sampler once
    UseShader(s_State.shader);
    SetUniformInt(s_State.shader, "u_Texture", 0);

    spdlog::info("[Renderer2D] Initialized (max {} quads)", MaxQuads);
}

void Shutdown()
{
    glDeleteVertexArrays(1, &s_State.vao);
    glDeleteBuffers(1, &s_State.vbo);
    glDeleteBuffers(1, &s_State.ibo);
    DeleteShader(s_State.shader);
    s_State = {};
    spdlog::info("[Renderer2D] Shutdown");
}

// ---------------------------------------------------------------------------
// Frame helpers
// ---------------------------------------------------------------------------

static void Flush()
{
    if (s_State.quadCount == 0) return;

    glBindTexture(GL_TEXTURE_2D, s_State.currentTexture);

    glBindBuffer(GL_ARRAY_BUFFER, s_State.vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0,
                    static_cast<GLsizeiptr>(s_State.quadCount * 4 * sizeof(QuadVertex)),
                    s_State.vertexBuffer.data());

    glBindVertexArray(s_State.vao);
    UseShader(s_State.shader);
    SetUniformMat4(s_State.shader, "u_ViewProj", s_State.viewProj);

    glDrawElements(GL_TRIANGLES,
                   static_cast<GLsizei>(s_State.quadCount * 6),
                   GL_UNSIGNED_INT, nullptr);

    s_State.quadCount      = 0;
    s_State.currentTexture = 0;
}

void BeginScene()
{
    s_State.quadCount      = 0;
    s_State.currentTexture = 0;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void EndScene()
{
    Flush();
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

// ---------------------------------------------------------------------------
// Drawing
// ---------------------------------------------------------------------------

void DrawTexture(const Texture2D& tex,
                 glm::vec2        pos,
                 glm::vec2        size,
                 glm::vec4        tint)
{
    // If this quad would use a different texture, flush first
    if (s_State.currentTexture != 0 && s_State.currentTexture != tex.id)
        Flush();

    // If the batch is full, flush first
    if (s_State.quadCount >= MaxQuads)
        Flush();

    s_State.currentTexture = tex.id;

    float x0 = pos.x - size.x * 0.5f;
    float x1 = pos.x + size.x * 0.5f;
    float y0 = pos.y - size.y * 0.5f;
    float y1 = pos.y + size.y * 0.5f;

    uint32_t base = s_State.quadCount * 4;

    // Bottom-left
    s_State.vertexBuffer[base + 0] = { x0, y0, 0.0f, 0.0f, tint.r, tint.g, tint.b, tint.a };
    // Bottom-right
    s_State.vertexBuffer[base + 1] = { x1, y0, 1.0f, 0.0f, tint.r, tint.g, tint.b, tint.a };
    // Top-right
    s_State.vertexBuffer[base + 2] = { x1, y1, 1.0f, 1.0f, tint.r, tint.g, tint.b, tint.a };
    // Top-left
    s_State.vertexBuffer[base + 3] = { x0, y1, 0.0f, 1.0f, tint.r, tint.g, tint.b, tint.a };

    ++s_State.quadCount;
}

// ---------------------------------------------------------------------------
// Camera
// ---------------------------------------------------------------------------

void SetViewProjection(const glm::mat4& vp)
{
    s_State.viewProj = vp;
}

} // namespace Renderer2D
} // namespace Rivet
