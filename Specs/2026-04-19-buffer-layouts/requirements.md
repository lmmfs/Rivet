# Phase 5 — Buffer Layouts: Requirements

## Scope

Introduce a typed vertex-layout system that replaces the manual `SetVertexAttrib` call
with a declarative description of vertex data. The deliverable is a Sandbox that renders
a colored triangle driven by two separate `BufferLayout`s — one for position, one for
color — with no hardcoded attribute pointers anywhere in application code.

### In scope
- `ShaderDataType` enum (`Float`, `Float2`, `Float3`, `Float4`, `Mat3`, `Mat4`,
  `Int`, `Int2`, `Int3`, `Int4`, `Bool`)
- Free helper `ShaderDataTypeSize(ShaderDataType)` → `uint32_t` (byte size)
- Free helper `ShaderDataTypeToGL(ShaderDataType)` → `uint32_t` (GL type constant,
  e.g. `GL_FLOAT`)
- `BufferElement` struct: `Name` (`std::string`), `Type` (`ShaderDataType`),
  `Size` (`uint32_t`), `Offset` (`uint32_t`), `Normalized` (`bool`);
  constructor computes `Size` automatically via `ShaderDataTypeSize`
- `BufferLayout` value type: accepts an `std::initializer_list<BufferElement>`,
  auto-calculates per-element `Offset` and total `Stride` on construction
- `SetVertexArrayLayout(VertexArray va, VertexBuffer vb, const BufferLayout& layout)` —
  binds both objects, iterates the layout and calls `glVertexAttribPointer` +
  `glEnableVertexAttribArray` for each element; replaces `SetVertexAttrib`
- Full exposure through `Rivet/Rivet.h`
- Sandbox updated: two VBOs with independent layouts (position + color), no manual
  attribute calls

### Out of scope
- Interleaved layouts (all attributes in a single VBO) — deferred
- Instanced attributes (`glVertexAttribDivisor`)
- Layout serialisation / reflection
- Removing the existing `SetVertexAttrib` function from the public API (it remains
  available but undocumented; removal is a separate breaking-change task)

---

## API Style Decisions

**Value types, not handles**
`BufferElement` and `BufferLayout` are stack-allocated value types passed by const
reference. They carry no GPU state — they only describe data shape. This keeps them
lightweight and consistent with the mission's preference for simplicity.

**Constructor computes `Size` automatically**
`BufferElement` takes `(ShaderDataType, const std::string& name, bool normalized = false)`.
The constructor calls `ShaderDataTypeSize` to populate `Size`; `Offset` starts at `0`
and is filled in by `BufferLayout` during construction.

**`BufferLayout` calculates offsets and stride once**
On construction, `BufferLayout` iterates its elements, accumulates `Offset` for each,
and records the running total as `Stride`. No recalculation at bind time.

**`SetVertexArrayLayout` is the only bind-time API**
Application code never calls `glVertexAttribPointer` directly. The free function
handles all GL state changes, keeping the Sandbox layer free of raw OpenGL.

```cpp
// Intended Sandbox usage
float positions[] = { -0.5f, -0.5f, 0.0f,
                       0.5f, -0.5f, 0.0f,
                       0.0f,  0.5f, 0.0f };

float colors[] = { 1.0f, 0.0f, 0.0f,
                   0.0f, 1.0f, 0.0f,
                   0.0f, 0.0f, 1.0f };

Rivet::VertexArray  va  = Rivet::CreateVertexArray();
Rivet::VertexBuffer vbP = Rivet::CreateVertexBuffer(positions, sizeof(positions));
Rivet::VertexBuffer vbC = Rivet::CreateVertexBuffer(colors,    sizeof(colors));

Rivet::BufferLayout posLayout = { { Rivet::ShaderDataType::Float3, "a_Position" } };
Rivet::BufferLayout colLayout = { { Rivet::ShaderDataType::Float3, "a_Color"    } };

Rivet::SetVertexArrayLayout(va, vbP, posLayout); // attrib index 0
Rivet::SetVertexArrayLayout(va, vbC, colLayout); // attrib index 1
```

**Attribute index is derived from element order across calls**
`SetVertexArrayLayout` maintains a monotonically incrementing attrib index per VAO
(tracked as a simple `uint32_t` stored alongside the VAO, or passed explicitly as a
parameter — implementation may choose). Starting index for a fresh VAO is `0`.
