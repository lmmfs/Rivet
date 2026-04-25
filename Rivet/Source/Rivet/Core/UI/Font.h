#pragma once

#include <string>
#include <cstdint>
#include <glm/glm.hpp>

namespace Rivet::UI {

    // Per-glyph data extracted from the atlas at load time.
    // All coordinates are in font-pixel units (at the baked font size).
    struct GlyphInfo
    {
        float x0, y0;     // offset from cursor to glyph top-left
        float x1, y1;     // offset from cursor to glyph bottom-right
        float s0, t0;     // atlas UV top-left (normalised 0-1)
        float s1, t1;     // atlas UV bottom-right
        float advance;    // horizontal cursor advance
    };

    struct Font
    {
        uint32_t  atlasTexture = 0;
        int       atlasWidth   = 512;
        int       atlasHeight  = 512;
        float     size         = 0.0f;   // baked point size (pixels)
        float     ascent       = 0.0f;   // pixels above baseline
        float     descent      = 0.0f;   // pixels below baseline (positive value)
        float     lineHeight   = 0.0f;   // ascent + descent + lineGap

        GlyphInfo glyphs[96] = {};       // ASCII 32 (' ') to 127 ('~')
    };

    // Load a TTF file and bake it into a GPU atlas.
    // Returns a Font with atlasTexture == 0 on failure.
    Font LoadFont(const std::string& path, float size);

    // Release the GPU atlas texture.
    void UnloadFont(Font& font);

    // Returns the pixel dimensions of text rendered with this font at the given scale.
    glm::vec2 MeasureText(const Font& font, const std::string& text, float scale = 1.0f);

} // namespace Rivet::UI
