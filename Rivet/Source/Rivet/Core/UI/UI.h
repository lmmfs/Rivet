#pragma once

#include "Font.h"

#include <glm/glm.hpp>
#include <functional>
#include <string>

namespace Rivet::UI {

    // -------------------------------------------------------------------------
    // Scene management
    // Sets a screen-space (pixel) orthographic projection so all UI coordinates
    // are in pixels with (0,0) at the top-left of the window.
    // Must wrap all UI draw calls.
    // -------------------------------------------------------------------------
    void BeginScene();
    void EndScene();

    // -------------------------------------------------------------------------
    // Panel — coloured background rectangle
    // position: top-left corner in screen pixels
    // -------------------------------------------------------------------------
    struct Panel
    {
        glm::vec2 position = { 0.0f, 0.0f };
        glm::vec2 size     = { 100.0f, 50.0f };
        glm::vec4 color    = { 0.15f, 0.15f, 0.15f, 0.85f };
    };

    void DrawPanel(const Panel& panel);

    // -------------------------------------------------------------------------
    // Label — text rendered from a Font atlas
    // position: top-left of the text bounding box in screen pixels
    // -------------------------------------------------------------------------
    struct Label
    {
        std::string  text;
        glm::vec2    position = { 0.0f, 0.0f };
        const Font*  font     = nullptr;
        glm::vec4    color    = { 1.0f, 1.0f, 1.0f, 1.0f };
        float        scale    = 1.0f;
    };

    void DrawLabel(const Label& label);

    // -------------------------------------------------------------------------
    // Button — Panel + Label with click callback
    // The label is centred inside the panel automatically.
    // -------------------------------------------------------------------------
    struct Button
    {
        Panel                 panel;
        Label                 label;
        std::function<void()> onClick;
    };

    void DrawButton(const Button& button);

    // Returns true if the button was clicked this frame.
    // Call once per frame before DrawButton, passing the current mouse position
    // and whether the left mouse button was just pressed.
    bool UpdateButton(const Button& button, glm::vec2 mousePos, bool mousePressed);

    // -------------------------------------------------------------------------
    // HealthBar — two-layer filled rectangle
    // position: top-left corner in screen pixels
    // fill:     normalised value in [0, 1]
    // -------------------------------------------------------------------------
    struct HealthBar
    {
        glm::vec2 position = { 0.0f, 0.0f };
        glm::vec2 size     = { 200.0f, 20.0f };
        float     fill     = 1.0f;
        glm::vec4 bgColor  = { 0.20f, 0.08f, 0.08f, 0.90f };
        glm::vec4 fgColor  = { 0.80f, 0.20f, 0.20f, 0.90f };
    };

    void DrawHealthBar(const HealthBar& bar);

} // namespace Rivet::UI
