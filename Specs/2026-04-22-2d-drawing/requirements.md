# Phase 7 — 2D Drawing: Requirements

## Scope

Implement a 2D drawing subsystem for Rivet that supports textured quad rendering, sprite batching, an orthographic camera, and texture loading via stb_image.

## Goals

- Render textured quads (sprites) to the screen using OpenGL.
- Batch multiple sprites sharing the same texture into a single draw call.
- Provide a 2D orthographic camera with pan and zoom.
- Load textures from disk using the vendored stb_image library.

## Out of Scope

- 3D rendering.
- Sprite sheets / animation (future phase).
- Font rendering.
- Custom blend modes (use standard alpha blending).

## API Decisions

- **Style:** Free functions only, consistent with Rivet's raylib-style procedural API.
- **Camera:** `BeginCamera2D(camera)` / `EndCamera2D()` pair that sets the view-projection uniform.
- **Drawing:** `DrawTexture(texture, position, size, tint)` and `DrawTextureEx(...)` for rotation/scale.
- **Texture:** Represented as an opaque `Texture2D` handle (ID + width/height).
- **Batching:** Sprites sharing the same texture are flushed in a single draw call; texture change triggers a flush.

## Context & References

- Tech stack: OpenGL 4.6 Core, GLAD 2, GLM for math, stb_image for texture loading.
- Builds on Phase 4 (VAO/VBO abstractions) and Phase 5 (BufferLayout).
- Camera projection uses `glm::ortho`.
- Batch max size: 1000 quads per flush (hard-coded constant, can be tuned).
