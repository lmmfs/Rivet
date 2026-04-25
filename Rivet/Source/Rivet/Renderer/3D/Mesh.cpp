#include "Mesh.h"

#include <glad/gl.h>

namespace Rivet {

Mesh CreateMesh(const std::vector<Vertex3D>& vertices,
                const std::vector<uint32_t>& indices)
{
    Mesh mesh;
    mesh.indexCount = static_cast<uint32_t>(indices.size());

    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);

    // Vertex buffer
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex3D)),
                 vertices.data(), GL_STATIC_DRAW);

    // location 0 — position (vec3)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
                          reinterpret_cast<void*>(offsetof(Vertex3D, position)));
    // location 1 — normal (vec3)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
                          reinterpret_cast<void*>(offsetof(Vertex3D, normal)));
    // location 2 — uv (vec2)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
                          reinterpret_cast<void*>(offsetof(Vertex3D, uv)));

    // Index buffer
    glGenBuffers(1, &mesh.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(indices.size() * sizeof(uint32_t)),
                 indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
    return mesh;
}

void DeleteMesh(Mesh& mesh)
{
    if (mesh.ibo) glDeleteBuffers(1, &mesh.ibo);
    if (mesh.vbo) glDeleteBuffers(1, &mesh.vbo);
    if (mesh.vao) glDeleteVertexArrays(1, &mesh.vao);
    mesh = {};
}

void DrawMesh(const Mesh& mesh)
{
    glBindVertexArray(mesh.vao);
    glDrawElements(GL_TRIANGLES,
                   static_cast<GLsizei>(mesh.indexCount),
                   GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

Mesh CreateCubeMesh()
{
    // 6 faces × 4 unique vertices each = 24 vertices
    // Each face has its own normals/UVs so vertices cannot be shared across faces.
    const std::vector<Vertex3D> verts = {
        // Front face (+Z)
        {{ -0.5f, -0.5f,  0.5f }, { 0.0f,  0.0f,  1.0f }, { 0.0f, 0.0f }},
        {{  0.5f, -0.5f,  0.5f }, { 0.0f,  0.0f,  1.0f }, { 1.0f, 0.0f }},
        {{  0.5f,  0.5f,  0.5f }, { 0.0f,  0.0f,  1.0f }, { 1.0f, 1.0f }},
        {{ -0.5f,  0.5f,  0.5f }, { 0.0f,  0.0f,  1.0f }, { 0.0f, 1.0f }},
        // Back face (-Z)
        {{  0.5f, -0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f }, { 0.0f, 0.0f }},
        {{ -0.5f, -0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f }},
        {{ -0.5f,  0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f }, { 1.0f, 1.0f }},
        {{  0.5f,  0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f }, { 0.0f, 1.0f }},
        // Left face (-X)
        {{ -0.5f, -0.5f, -0.5f }, {-1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f }},
        {{ -0.5f, -0.5f,  0.5f }, {-1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f }},
        {{ -0.5f,  0.5f,  0.5f }, {-1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f }},
        {{ -0.5f,  0.5f, -0.5f }, {-1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f }},
        // Right face (+X)
        {{  0.5f, -0.5f,  0.5f }, { 1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f }},
        {{  0.5f, -0.5f, -0.5f }, { 1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f }},
        {{  0.5f,  0.5f, -0.5f }, { 1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f }},
        {{  0.5f,  0.5f,  0.5f }, { 1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f }},
        // Top face (+Y)
        {{ -0.5f,  0.5f,  0.5f }, { 0.0f,  1.0f,  0.0f }, { 0.0f, 0.0f }},
        {{  0.5f,  0.5f,  0.5f }, { 0.0f,  1.0f,  0.0f }, { 1.0f, 0.0f }},
        {{  0.5f,  0.5f, -0.5f }, { 0.0f,  1.0f,  0.0f }, { 1.0f, 1.0f }},
        {{ -0.5f,  0.5f, -0.5f }, { 0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f }},
        // Bottom face (-Y)
        {{ -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f,  0.0f }, { 0.0f, 0.0f }},
        {{  0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f }},
        {{  0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f }},
        {{ -0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f }},
    };

    std::vector<uint32_t> indices;
    indices.reserve(36);
    for (uint32_t face = 0; face < 6; ++face)
    {
        uint32_t b = face * 4;
        indices.push_back(b + 0); indices.push_back(b + 1); indices.push_back(b + 2);
        indices.push_back(b + 2); indices.push_back(b + 3); indices.push_back(b + 0);
    }

    return CreateMesh(verts, indices);
}

} // namespace Rivet
