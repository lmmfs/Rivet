#include "Texture.h"

#include <glad/gl.h>
#include <stb_image.h>
#include <spdlog/spdlog.h>

namespace Rivet {

    Texture2D LoadTexture(const std::string& path)
    {
        Texture2D tex{};

        stbi_set_flip_vertically_on_load(1);
        unsigned char* data = stbi_load(path.c_str(), &tex.width, &tex.height, &tex.channels, 4);
        if (!data)
        {
            spdlog::error("[Rivet] LoadTexture failed: {}", stbi_failure_reason());
            return tex;
        }

        glGenTextures(1, &tex.id);
        glBindTexture(GL_TEXTURE_2D, tex.id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
                     tex.width, tex.height, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);

        tex.channels = 4;
        spdlog::info("[Rivet] LoadTexture: {} ({}x{})", path, tex.width, tex.height);
        return tex;
    }

    void UnloadTexture(Texture2D& tex)
    {
        if (tex.id)
        {
            glDeleteTextures(1, &tex.id);
            tex = {};
        }
    }

} // namespace Rivet
