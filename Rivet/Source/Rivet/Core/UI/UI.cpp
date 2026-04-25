#include "UI.h"
#include "../App.h"
#include "../../Renderer/2D/Renderer.h"
#include "../../Renderer/Common/Texture.h"

#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

namespace Rivet::UI {

    // -------------------------------------------------------------------------
    // Scene management
    // -------------------------------------------------------------------------

    void BeginScene()
    {
        glm::ivec2 winSize = Rivet::GetWindowSize();
        // Screen-space orthographic: (0,0) top-left, (w,h) bottom-right.
        // Y increases downward which matches screen convention.
        glm::mat4 screenProj = glm::ortho(
            0.0f, static_cast<float>(winSize.x),
            static_cast<float>(winSize.y), 0.0f,
            -1.0f, 1.0f);

        Renderer2D::SetViewProjection(screenProj);
        Renderer2D::BeginScene();
    }

    void EndScene()
    {
        Renderer2D::EndScene();
        // Restore identity so the world renderer is not affected if called after.
        Renderer2D::SetViewProjection(glm::mat4(1.0f));
    }

    // -------------------------------------------------------------------------
    // Panel
    // -------------------------------------------------------------------------

    void DrawPanel(const Panel& panel)
    {
        // Renderer2D::DrawQuad expects the centre position.
        glm::vec2 center = panel.position + panel.size * 0.5f;
        Renderer2D::DrawQuad(center, panel.size, panel.color);
    }

    // -------------------------------------------------------------------------
    // Label
    // -------------------------------------------------------------------------

    void DrawLabel(const Label& label)
    {
        if (!label.font || label.font->atlasTexture == 0) return;
        if (label.text.empty()) return;

        const Font& font = *label.font;

        // Wrap the atlas in a Texture2D so Renderer2D can manage it.
        Texture2D atlas{};
        atlas.id     = font.atlasTexture;
        atlas.width  = font.atlasWidth;
        atlas.height = font.atlasHeight;

        // Pen starts at the left edge; y=0 is the baseline in font space.
        // We offset by ascent so label.position.y is the visual top of the text.
        float cursor = 0.0f;

        for (char ch : label.text)
        {
            unsigned char uc = static_cast<unsigned char>(ch);
            if (uc < 32 || uc > 127) continue;

            const GlyphInfo& g = font.glyphs[uc - 32];

            // Convert font-space quad to screen pixels.
            float sx0 = label.position.x + (cursor + g.x0) * label.scale;
            float sx1 = label.position.x + (cursor + g.x1) * label.scale;
            float sy0 = label.position.y + (font.ascent + g.y0) * label.scale;
            float sy1 = label.position.y + (font.ascent + g.y1) * label.scale;

            glm::vec2 center = { (sx0 + sx1) * 0.5f, (sy0 + sy1) * 0.5f };
            glm::vec2 size   = { sx1 - sx0, sy1 - sy0 };

            Renderer2D::DrawTextureRegion(
                atlas, center, size,
                { g.s0, g.t0 }, { g.s1, g.t1 },
                label.color);

            cursor += g.advance;
        }
    }

    // -------------------------------------------------------------------------
    // Button
    // -------------------------------------------------------------------------

    void DrawButton(const Button& button)
    {
        DrawPanel(button.panel);

        // Centre the label inside the panel.
        if (button.label.font)
        {
            glm::vec2 textSize = MeasureText(*button.label.font,
                                             button.label.text,
                                             button.label.scale);
            Label l = button.label;
            l.position = button.panel.position
                       + button.panel.size * 0.5f
                       - textSize * 0.5f;
            DrawLabel(l);
        }
    }

    bool UpdateButton(const Button& button, glm::vec2 mousePos, bool mousePressed)
    {
        const Panel& p = button.panel;
        bool inside = mousePos.x >= p.position.x
                   && mousePos.x <= p.position.x + p.size.x
                   && mousePos.y >= p.position.y
                   && mousePos.y <= p.position.y + p.size.y;

        if (inside && mousePressed && button.onClick)
        {
            button.onClick();
            return true;
        }
        return false;
    }

    // -------------------------------------------------------------------------
    // HealthBar
    // -------------------------------------------------------------------------

    void DrawHealthBar(const HealthBar& bar)
    {
        float fill = std::clamp(bar.fill, 0.0f, 1.0f);

        // Background quad (full size).
        glm::vec2 bgCenter = bar.position + bar.size * 0.5f;
        Renderer2D::DrawQuad(bgCenter, bar.size, bar.bgColor);

        // Foreground quad (proportional width, anchored to the left edge).
        if (fill > 0.0f)
        {
            glm::vec2 fgSize   = { bar.size.x * fill, bar.size.y };
            glm::vec2 fgCenter = { bar.position.x + fgSize.x * 0.5f,
                                   bar.position.y + bar.size.y * 0.5f };
            Renderer2D::DrawQuad(fgCenter, fgSize, bar.fgColor);
        }
    }

} // namespace Rivet::UI
