#pragma once

#include "Texture.h"

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

        // Internal — used by Camera2D.
        void SetViewProjection(const glm::mat4& vp);

    } // namespace Renderer2D

} // namespace Rivet
