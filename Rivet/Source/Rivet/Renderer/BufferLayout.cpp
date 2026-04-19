#include "BufferLayout.h"

#include "Rvtph.h"

#include <unordered_map>

namespace Rivet {

    // -------------------------------------------------------------------------
    // ShaderDataType helpers
    // -------------------------------------------------------------------------

    uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:  return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Mat3:   return 4 * 3 * 3;
            case ShaderDataType::Mat4:   return 4 * 4 * 4;
            case ShaderDataType::Int:    return 4;
            case ShaderDataType::Int2:   return 4 * 2;
            case ShaderDataType::Int3:   return 4 * 3;
            case ShaderDataType::Int4:   return 4 * 4;
            case ShaderDataType::Bool:   return 4;
            default:                     return 0;
        }
    }

    uint32_t ShaderDataTypeToGL(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:   return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:   return GL_INT;
            case ShaderDataType::Bool:   return GL_BOOL;
            default:                     return 0;
        }
    }

    uint32_t GetComponentCount(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:  return 1;
            case ShaderDataType::Float2: return 2;
            case ShaderDataType::Float3: return 3;
            case ShaderDataType::Float4: return 4;
            case ShaderDataType::Mat3:   return 3;
            case ShaderDataType::Mat4:   return 4;
            case ShaderDataType::Int:    return 1;
            case ShaderDataType::Int2:   return 2;
            case ShaderDataType::Int3:   return 3;
            case ShaderDataType::Int4:   return 4;
            case ShaderDataType::Bool:   return 1;
            default:                     return 0;
        }
    }

    // -------------------------------------------------------------------------
    // BufferElement
    // -------------------------------------------------------------------------

    BufferElement::BufferElement(ShaderDataType type, const std::string& name, bool normalized)
        : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
    {
    }

    // -------------------------------------------------------------------------
    // BufferLayout
    // -------------------------------------------------------------------------

    BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements)
        : m_Elements(elements)
    {
        CalculateOffsetsAndStride();
    }

    void BufferLayout::CalculateOffsetsAndStride()
    {
        uint32_t offset = 0;
        for (auto& element : m_Elements)
        {
            element.Offset = offset;
            offset += element.Size;
        }
        m_Stride = offset;
    }

    // -------------------------------------------------------------------------
    // SetVertexArrayLayout
    // -------------------------------------------------------------------------

    // Tracks the next free attrib index for each VAO so successive calls
    // on the same VAO assign non-overlapping indices.
    static std::unordered_map<VertexArray, uint32_t> s_AttribIndexMap;

    void SetVertexArrayLayout(VertexArray va, VertexBuffer vb, const BufferLayout& layout)
    {
        BindVertexArray(va);
        BindVertexBuffer(vb);

        uint32_t& index = s_AttribIndexMap[va];

        for (const auto& element : layout.GetElements())
        {
            glVertexAttribPointer(
                index,
                static_cast<GLint>(GetComponentCount(element.Type)),
                ShaderDataTypeToGL(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                static_cast<GLsizei>(layout.GetStride()),
                reinterpret_cast<const void*>(static_cast<uintptr_t>(element.Offset)));
            glEnableVertexAttribArray(index);
            ++index;
        }
    }

} // namespace Rivet
