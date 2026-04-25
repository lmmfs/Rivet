#pragma once

#include "../Common/Texture.h"

#include <glm/glm.hpp>

namespace Rivet {

    // -------------------------------------------------------------------------
    // Renderer2D — sprite batch renderer
    // -------------------------------------------------------------------------

    namespace Renderer2D {

        void Init();
        void Shutdown();

        // Call once per frame before any DrawTexture calls.
        void BeginScene();
        // Flushes remaining quads and ends the scene.
        void EndScene();

        // Draw a textured quad.
        // pos    — centre of the quad in world space.
        // size   — width and height in world units.
        // tint   — RGBA multiplier applied in the fragment shader.
        void DrawTexture(const Texture2D& tex,
                         glm::vec2        pos,
                         glm::vec2        size,
                         glm::vec4        tint = { 1, 1, 1, 1 });

        // Draw a solid-color quad (no texture needed).
        void DrawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color);

        // Draw a sub-region of a texture (e.g. glyph from a font atlas).
        // uvMin/uvMax are normalised UV coordinates (0-1).
        void DrawTextureRegion(const Texture2D& tex,
                               glm::vec2        pos,
                               glm::vec2        size,
                               glm::vec2        uvMin,
                               glm::vec2        uvMax,
                               glm::vec4        tint = { 1, 1, 1, 1 });

        // Internal — used by Camera2D.
        void SetViewProjection(const glm::mat4& vp);

    } // namespace Renderer2D

} // namespace Rivet
