#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace Rivet {

    using Shader = uint32_t;

    // Load, compile, and link a GLSL program from two file paths.
    // Returns 0 on failure (errors are logged via spdlog).
    Shader LoadShader(const char* vertexPath, const char* fragmentPath);
    void   DeleteShader(Shader shader);
    void   UseShader(Shader shader);

    // Uniform setters — resolve location by name each call.
    void SetUniformInt  (Shader shader, const char* name, int value);
    void SetUniformFloat(Shader shader, const char* name, float value);
    void SetUniformVec2 (Shader shader, const char* name, glm::vec2 value);
    void SetUniformVec3 (Shader shader, const char* name, glm::vec3 value);
    void SetUniformVec4 (Shader shader, const char* name, glm::vec4 value);
    void SetUniformMat4 (Shader shader, const char* name, const glm::mat4& value);

}
