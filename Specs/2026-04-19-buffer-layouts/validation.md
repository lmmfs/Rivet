# Phase 5 — Buffer Layouts: Validation

## Merge Criteria

All of the following must be true before this branch is merged into `main`.

---

### 1. Build

- [ ] `cmake --build build` completes with zero errors and zero warnings on the target
      platform (Linux / Wayland).
- [ ] The precompiled header (`Rvtph.h`) is not broken by any new include.
- [ ] `Sandbox` compiles including only `<Rivet/Rivet.h>` — no direct `<glad/gl.h>`
      in `Main.cpp`.
- [ ] `BufferLayout.h` / `BufferLayout.cpp` are the only new files added to the
      `Rivet` target; no stray files remain.

---

### 2. ShaderDataType Helpers

- [ ] `ShaderDataTypeSize` returns the correct byte count for every enum value
      (spot-check: `Float` → 4, `Float3` → 12, `Mat4` → 64, `Bool` → 4).
- [ ] `ShaderDataTypeToGL` maps every enum value to a valid GL constant without
      triggering a `GL_INVALID_ENUM` error when passed to `glVertexAttribPointer`.
- [ ] Passing `ShaderDataType::None` to either helper does not crash — it returns
      `0` or asserts clearly in debug builds.

---

### 3. BufferElement Construction

- [ ] A `BufferElement` constructed with `(Float3, "a_Position")` reports
      `Size == 12`, `Offset == 0` (before being added to a layout), `Normalized == false`.
- [ ] A `BufferElement` constructed with `(Float3, "a_Color", true)` reports
      `Normalized == true`.
- [ ] `Size` is never `0` for any valid `ShaderDataType`.

---

### 4. BufferLayout Offsets & Stride

- [ ] A layout with a single `Float3` element has `Stride == 12` and that element's
      `Offset == 0`.
- [ ] A hypothetical interleaved layout `{ Float3, Float2 }` would produce offsets
      `0` and `12` and stride `20` (verified by unit inspection or a local test).
- [ ] A default-constructed `BufferLayout` has `Stride == 0` and an empty element
      list — no crash.

---

### 5. SetVertexArrayLayout

- [ ] Calling `SetVertexArrayLayout(va, vb, layout)` leaves no pending `glGetError`
      on a GL debug context.
- [ ] Each element in the layout maps to a unique, correctly incremented attribute
      index — confirmed by the rendered output (correct positions and colors,
      not swapped or garbled).
- [ ] After the call, the VAO retains the attribute state when re-bound — rebinding
      and drawing without calling `SetVertexArrayLayout` again still works.

---

### 6. Sandbox Demo

- [ ] Sandbox renders a triangle with three distinct vertex colors (e.g. red at
      bottom-left, green at bottom-right, blue at top) interpolated by the GPU.
- [ ] Color data lives in a dedicated VBO (`vbColor`) described by a `colLayout`
      containing a single `Float3` element — no hardcoded attribute index or stride
      in `Main.cpp`.
- [ ] Position data lives in a separate VBO (`vbPosition`) described by a
      `posLayout` containing a single `Float3` element.
- [ ] `SetVertexAttrib` is not called anywhere in `Main.cpp`.
- [ ] The fragment shader uses the interpolated `v_Color` varying, not a uniform.
- [ ] FPS logging and window resize behavior are unaffected.

---

### 7. API Surface

- [ ] `ShaderDataType`, `BufferElement`, `BufferLayout`, and `SetVertexArrayLayout`
      are all accessible via `#include <Rivet/Rivet.h>` with no additional includes.
- [ ] `SetVertexAttrib` remains compilable (no removal in this phase).
