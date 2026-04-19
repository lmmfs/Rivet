#include "Buffer.h"

#include "Rvtph.h"

namespace Rivet {

    // -------------------------------------------------------------------------
    // VertexBuffer
    // -------------------------------------------------------------------------

    VertexBuffer CreateVertexBuffer(const float* data, uint32_t size)
    {
        uint32_t id;
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        return id;
    }

    void DeleteVertexBuffer(VertexBuffer vb)
    {
        glDeleteBuffers(1, &vb);
    }

    void BindVertexBuffer(VertexBuffer vb)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vb);
    }

    // -------------------------------------------------------------------------
    // IndexBuffer
    // -------------------------------------------------------------------------

    IndexBuffer CreateIndexBuffer(const uint32_t* data, uint32_t count)
    {
        uint32_t id;
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
        return id;
    }

    void DeleteIndexBuffer(IndexBuffer ib)
    {
        glDeleteBuffers(1, &ib);
    }

    void BindIndexBuffer(IndexBuffer ib)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    }

    // -------------------------------------------------------------------------
    // VertexArray
    // -------------------------------------------------------------------------

    VertexArray CreateVertexArray()
    {
        uint32_t id;
        glGenVertexArrays(1, &id);
        glBindVertexArray(id);
        return id;
    }

    void DeleteVertexArray(VertexArray va)
    {
        glDeleteVertexArrays(1, &va);
    }

    void BindVertexArray(VertexArray va)
    {
        glBindVertexArray(va);
    }

    void SetVertexAttrib(uint32_t index, int size, uint32_t stride, uint32_t offset)
    {
        glVertexAttribPointer(
            index, size, GL_FLOAT, GL_FALSE,
            static_cast<GLsizei>(stride),
            reinterpret_cast<const void*>(static_cast<uintptr_t>(offset)));
        glEnableVertexAttribArray(index);
    }

}
