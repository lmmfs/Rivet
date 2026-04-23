#include "Font.h"
#include "../Logger.h"

#include <stb_truetype.h>
#include <glad/gl.h>
#include <fstream>
#include <vector>
#include <algorithm>

namespace Rivet::UI {

    Font LoadFont(const std::string& path, float size)
    {
        Font font{};

        // ---- Read TTF file --------------------------------------------------
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file.is_open())
        {
            RVT_CORE_ERROR("[Font] Failed to open '{}'", path);
            return font;
        }
        std::streamsize fileSize = file.tellg();
        file.seekg(0, std::ios::beg);
        std::vector<unsigned char> ttfData(static_cast<size_t>(fileSize));
        file.read(reinterpret_cast<char*>(ttfData.data()), fileSize);

        // ---- Initialise font info -------------------------------------------
        stbtt_fontinfo info{};
        if (!stbtt_InitFont(&info, ttfData.data(), 0))
        {
            RVT_CORE_ERROR("[Font] stbtt_InitFont failed for '{}'", path);
            return font;
        }

        // ---- Compute metrics -----------------------------------------------
        float scale = stbtt_ScaleForPixelHeight(&info, size);
        int ascent_i, descent_i, lineGap_i;
        stbtt_GetFontVMetrics(&info, &ascent_i, &descent_i, &lineGap_i);

        font.ascent     =  static_cast<float>(ascent_i)  * scale;
        font.descent    = -static_cast<float>(descent_i) * scale;  // stored positive
        font.lineHeight =  (static_cast<float>(ascent_i - descent_i + lineGap_i)) * scale;
        font.size       = size;

        // ---- Pack glyph atlas ----------------------------------------------
        constexpr int AtlasW = 512;
        constexpr int AtlasH = 512;

        std::vector<unsigned char> bitmap(AtlasW * AtlasH, 0);
        stbtt_packedchar packChars[96];

        stbtt_pack_context ctx;
        stbtt_PackBegin(&ctx, bitmap.data(), AtlasW, AtlasH, 0, 1, nullptr);
        stbtt_PackSetOversampling(&ctx, 2, 2);
        stbtt_PackFontRange(&ctx, ttfData.data(), 0, size, 32, 96, packChars);
        stbtt_PackEnd(&ctx);

        // ---- Extract glyph data -------------------------------------------
        for (int i = 0; i < 96; ++i)
        {
            float px = 0.0f, py = 0.0f;
            stbtt_aligned_quad q;
            stbtt_GetPackedQuad(packChars, AtlasW, AtlasH, i, &px, &py, &q, 0);

            GlyphInfo& g = font.glyphs[i];
            g.x0      = q.x0;
            g.y0      = q.y0;
            g.x1      = q.x1;
            g.y1      = q.y1;
            g.s0      = q.s0;
            g.t0      = q.t0;
            g.s1      = q.s1;
            g.t1      = q.t1;
            g.advance = px;  // stbtt advanced px by the glyph advance width
        }

        // ---- Upload atlas as GL_RED with RGBA swizzle ----------------------
        font.atlasWidth  = AtlasW;
        font.atlasHeight = AtlasH;

        glGenTextures(1, &font.atlasTexture);
        glBindTexture(GL_TEXTURE_2D, font.atlasTexture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Replicate red channel into all four channels so the existing quad
        // shader (texture * tint) treats coverage as alpha and color.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_RED);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_RED);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_RED);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                     AtlasW, AtlasH, 0,
                     GL_RED, GL_UNSIGNED_BYTE, bitmap.data());
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

        glBindTexture(GL_TEXTURE_2D, 0);

        RVT_CORE_INFO("[Font] Loaded '{}' @ {}px (ascent={:.1f}, lineH={:.1f})",
                      path, size, font.ascent, font.lineHeight);
        return font;
    }

    void UnloadFont(Font& font)
    {
        if (font.atlasTexture)
        {
            glDeleteTextures(1, &font.atlasTexture);
            font = {};
        }
    }

    glm::vec2 MeasureText(const Font& font, const std::string& text, float scale)
    {
        float cursor = 0.0f;
        for (char c : text)
        {
            if (c < 32 || c > 127) continue;
            cursor += font.glyphs[static_cast<unsigned char>(c) - 32].advance;
        }
        return { cursor * scale, font.lineHeight * scale };
    }

} // namespace Rivet::UI
