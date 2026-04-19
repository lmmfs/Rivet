#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <initializer_list>

#include "Buffer.h"

namespace Rivet {

    // -------------------------------------------------------------------------
    // ShaderDataType
    // -------------------------------------------------------------------------

    enum class ShaderDataType : uint8_t
    {
        None = 0,
        Float, Float2, Float3, Float4,
        Mat3,  Mat4,
        Int,   Int2,   Int3,   Int4,
        Bool
    };

    uint32_t ShaderDataTypeSize(ShaderDataType type);
    uint32_t ShaderDataTypeToGL(ShaderDataType type);
    uint32_t GetComponentCount(ShaderDataType type);

    // -------------------------------------------------------------------------
    // BufferElement
    // -------------------------------------------------------------------------

    struct BufferElement
    {
        std::string    Name;
        ShaderDataType Type;
        uint32_t       Size;
        uint32_t       Offset;
        bool           Normalized;

        BufferElement(ShaderDataType type, const std::string& name,
                      bool normalized = false);
    };

    // -------------------------------------------------------------------------
    // BufferLayout
    // -------------------------------------------------------------------------

    class BufferLayout
    {
    public:
        BufferLayout() = default;
        BufferLayout(std::initializer_list<BufferElement> elements);

        const std::vector<BufferElement>& GetElements() const { return m_Elements; }
        uint32_t GetStride() const { return m_Stride; }

    private:
        std::vector<BufferElement> m_Elements;
        uint32_t                   m_Stride = 0;

        void CalculateOffsetsAndStride();
    };

    // Binds va and vb, then configures one vertex attribute per layout element.
    // Attrib indices are allocated monotonically per VAO across successive calls.
    void SetVertexArrayLayout(VertexArray va, VertexBuffer vb, const BufferLayout& layout);

} // namespace Rivet
