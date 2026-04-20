#pragma once

#include <string>
#include <glm/glm.hpp>

struct GLFWwindow;

namespace Rivet {

    void Init(const std::string& title = "Rivet", uint32_t width = 1280, uint32_t height = 720);
    bool ShouldClose();
    GLFWwindow* GetNativeWindow();
    void BeginFrame();
    void EndFrame();
    void Shutdown();

    void SetClearColor(float r, float g, float b, float a = 1.0f);
    void SetClearColor(const glm::vec4& color);
    void Clear();
    void SetViewport(int x, int y, int width, int height);

    glm::ivec2 GetWindowSize();

}
