#include "Shader.h"
#include "../../Core/Logger.h"

#include "Rvtph.h"

namespace Rivet {

    // -------------------------------------------------------------------------
    // Internal helpers
    // -------------------------------------------------------------------------

    static std::string ReadFile(const char* path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            RVT_CORE_ERROR("Shader: failed to open '{}'", path);
            return {};
        }
        std::ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    static uint32_t CompileStage(GLenum type, const char* source, const char* path)
    {
        uint32_t id = glCreateShader(type);
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char log[1024];
            glGetShaderInfoLog(id, sizeof(log), nullptr, log);
            RVT_CORE_ERROR("Shader compile error in '{}': {}", path, log);
            glDeleteShader(id);
            return 0;
        }
        return id;
    }

    // -------------------------------------------------------------------------
    // Public API
    // -------------------------------------------------------------------------

    Shader LoadShader(const char* vertexPath, const char* fragmentPath)
    {
        std::string vertSrc = ReadFile(vertexPath);
        std::string fragSrc = ReadFile(fragmentPath);

        if (vertSrc.empty() || fragSrc.empty())
            return 0;

        uint32_t vert = CompileStage(GL_VERTEX_SHADER,   vertSrc.c_str(), vertexPath);
        uint32_t frag = CompileStage(GL_FRAGMENT_SHADER, fragSrc.c_str(), fragmentPath);

        if (!vert || !frag)
        {
            if (vert) glDeleteShader(vert);
            if (frag) glDeleteShader(frag);
            return 0;
        }

        uint32_t program = glCreateProgram();
        glAttachShader(program, vert);
        glAttachShader(program, frag);
        glLinkProgram(program);

        glDeleteShader(vert);
        glDeleteShader(frag);

        int success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            char log[1024];
            glGetProgramInfoLog(program, sizeof(log), nullptr, log);
            RVT_CORE_ERROR("Shader link error (vert='{}', frag='{}'): {}", vertexPath, fragmentPath, log);
            glDeleteProgram(program);
            return 0;
        }

        RVT_CORE_INFO("Shader loaded: '{}' + '{}'", vertexPath, fragmentPath);
        return static_cast<Shader>(program);
    }

    void DeleteShader(Shader shader)
    {
        if (shader)
            glDeleteProgram(shader);
    }

    void UseShader(Shader shader)
    {
        glUseProgram(shader);
    }

    void SetUniformInt(Shader shader, const char* name, int value)
    {
        glUniform1i(glGetUniformLocation(shader, name), value);
    }

    void SetUniformFloat(Shader shader, const char* name, float value)
    {
        glUniform1f(glGetUniformLocation(shader, name), value);
    }

    void SetUniformVec2(Shader shader, const char* name, glm::vec2 value)
    {
        glUniform2f(glGetUniformLocation(shader, name), value.x, value.y);
    }

    void SetUniformVec3(Shader shader, const char* name, glm::vec3 value)
    {
        glUniform3f(glGetUniformLocation(shader, name), value.x, value.y, value.z);
    }

    void SetUniformVec4(Shader shader, const char* name, glm::vec4 value)
    {
        glUniform4f(glGetUniformLocation(shader, name), value.x, value.y, value.z, value.w);
    }

    void SetUniformMat4(Shader shader, const char* name, const glm::mat4& value)
    {
        glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, GL_FALSE, &value[0][0]);
    }

}
