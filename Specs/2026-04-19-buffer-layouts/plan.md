# Phase 5 — Buffer Layouts: Plan

## Group 1 — ShaderDataType Enum & Helpers

1. Create `Rivet/Source/Rivet/Renderer/BufferLayout.h`.
2. Define `enum class ShaderDataType : uint8_t` with values:
   `None`, `Float`, `Float2`, `Float3`, `Float4`,
   `Mat3`, `Mat4`, `Int`, `Int2`, `Int3`, `Int4`, `Bool`.
3. Implement free function `ShaderDataTypeSize(ShaderDataType type) -> uint32_t` —
   returns the byte size of each type (e.g. `Float` → 4, `Float2` → 8, `Mat4` → 64).
4. Implement free function `ShaderDataTypeToGL(ShaderDataType type) -> uint32_t` —
   returns the corresponding GL type constant (e.g. `Float*` → `GL_FLOAT`,
   `Int*` → `GL_INT`, `Bool` → `GL_BOOL`).
5. Add a `GetComponentCount(ShaderDataType type) -> uint32_t` helper used internally
   by `glVertexAttribPointer` (e.g. `Float3` → 3, `Mat4` → 4 columns of `Float4`).

## Group 2 — BufferElement Struct

6. Define `struct BufferElement` in `BufferLayout.h`:
   ```cpp
   struct BufferElement {
       std::string    Name;
       ShaderDataType Type;
       uint32_t       Size;
       uint32_t       Offset;
       bool           Normalized;

       BufferElement(ShaderDataType type, const std::string& name,
                     bool normalized = false);
   };
   ```
7. Implement the `BufferElement` constructor in `BufferLayout.cpp`:
   - Sets `Type`, `Name`, `Normalized`.
   - Calls `ShaderDataTypeSize(type)` to populate `Size`.
   - Initialises `Offset` to `0` (filled in by `BufferLayout`).

## Group 3 — BufferLayout Class

8. Define `class BufferLayout` in `BufferLayout.h`:
   ```cpp
   class BufferLayout {
   public:
       BufferLayout() = default;
       BufferLayout(std::initializer_list<BufferElement> elements);

       const std::vector<BufferElement>& GetElements() const;
       uint32_t GetStride() const;

   private:
       std::vector<BufferElement> m_Elements;
       uint32_t                   m_Stride = 0;
       void CalculateOffsetsAndStride();
   };
   ```
9. Implement `BufferLayout(std::initializer_list<BufferElement>)`:
   - Stores elements into `m_Elements`.
   - Calls `CalculateOffsetsAndStride()`.
10. Implement `CalculateOffsetsAndStride()`:
    - Walks `m_Elements` in order; sets each element's `Offset` to the running byte
      total, then advances the total by `element.Size`.
    - Stores the final total in `m_Stride`.
11. Add `BufferLayout.cpp` to the `Rivet` CMake target sources.

## Group 4 — Wire Layout into VertexArray

12. Add `SetVertexArrayLayout(VertexArray va, VertexBuffer vb, const BufferLayout& layout)`
    declaration to `Rivet/Source/Rivet/Renderer/VertexArray.h` (or a new
    `Renderer.h` if it fits better).
13. Implement `SetVertexArrayLayout` in the corresponding `.cpp`:
    - Binds `va` and `vb`.
    - Iterates `layout.GetElements()`.
    - For each element, calls `glVertexAttribPointer` (index, component count,
      GL type, normalized, stride, offset as void*) and `glEnableVertexAttribArray`.
    - Tracks the current attrib index; starts at `0` for the first call on a given
      VAO and increments per element, across calls on the same VAO.
14. Expose `ShaderDataType`, `BufferElement`, `BufferLayout`, and
    `SetVertexArrayLayout` through `Rivet/Rivet.h`.
15. Update `Sandbox/Main.cpp`:
    - Split the single interleaved VBO into two: `vbPosition` (Float3) and
      `vbColor` (Float3).
    - Declare a `posLayout` and a `colLayout` using brace-init syntax.
    - Replace all `SetVertexAttrib` calls with `SetVertexArrayLayout`.
    - Update `basic.vert` to accept `layout (location = 1) in vec3 a_Color` and
      pass it as a varying to the fragment shader.
    - Update `basic.frag` to use the interpolated color instead of the uniform.
16. Verify the build; confirm the colored triangle renders with no GL errors.
