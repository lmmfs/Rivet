#pragma once

#include <cstdint>

namespace Rivet {

    using VertexBuffer = uint32_t;
    using IndexBuffer  = uint32_t;
    using VertexArray  = uint32_t;

    // VertexBuffer — uploads float data to GL_ARRAY_BUFFER (GL_STATIC_DRAW).
    VertexBuffer CreateVertexBuffer(const float* data, uint32_t size);
    void         DeleteVertexBuffer(VertexBuffer vb);
    void         BindVertexBuffer(VertexBuffer vb);

    // IndexBuffer — uploads uint32 indices to GL_ELEMENT_ARRAY_BUFFER (GL_STATIC_DRAW).
    IndexBuffer  CreateIndexBuffer(const uint32_t* data, uint32_t count);
    void         DeleteIndexBuffer(IndexBuffer ib);
    void         BindIndexBuffer(IndexBuffer ib);

    // VertexArray — generates and binds a VAO.
    VertexArray  CreateVertexArray();
    void         DeleteVertexArray(VertexArray va);
    void         BindVertexArray(VertexArray va);

    // Configure a vertex attribute.  Must be called with the target VAO and VBO bound.
    // stride and offset are in bytes.
    void SetVertexAttrib(uint32_t index, int size, uint32_t stride, uint32_t offset);

}
