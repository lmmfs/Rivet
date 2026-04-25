#pragma once

#include <cstdint>
#include <vector>
#include <glm/glm.hpp>

namespace Rivet {

    // -------------------------------------------------------------------------
    // Vertex3D — interleaved vertex layout for 3D geometry
    //   location 0 : position  (vec3)
    //   location 1 : normal    (vec3)
    //   location 2 : uv        (vec2)
    // -------------------------------------------------------------------------

    struct Vertex3D
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

    // -------------------------------------------------------------------------
    // Mesh — GPU-ready indexed geometry
    // -------------------------------------------------------------------------

    struct Mesh
    {
        uint32_t vao        = 0;
        uint32_t vbo        = 0;
        uint32_t ibo        = 0;
        uint32_t indexCount = 0;
    };

    // Upload vertex + index data to the GPU.
    Mesh CreateMesh(const std::vector<Vertex3D>& vertices,
                    const std::vector<uint32_t>& indices);

    // Release GPU resources and zero-out the struct.
    void DeleteMesh(Mesh& mesh);

    // Bind the VAO and issue a single indexed draw call.
    void DrawMesh(const Mesh& mesh);

    // Convenience: unit cube (1×1×1 centred at origin, 36 indices).
    Mesh CreateCubeMesh();

} // namespace Rivet
