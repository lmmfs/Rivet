#include "App.h"
#include "Window.h"
#include "Input.h"
#include "Logger.h"

#include <glad/gl.h>

#include <memory>

namespace Rivet {

    static std::unique_ptr<Window> s_Window;
    static glm::vec4 s_ClearColor{ 0.0f, 0.0f, 0.0f, 1.0f };

    void Init(const std::string& title, uint32_t width, uint32_t height)
    {
        Log::Init();

        WindowSpecification spec;
        spec.Title  = title;
        spec.Width  = width;
        spec.Height = height;

        s_Window = std::make_unique<Window>(spec);
        s_Window->Create();

        Input::Init(s_Window->GetHandle());

        RVT_CORE_INFO("Rivet initialized: {}x{}", width, height);
    }

    bool ShouldClose()
    {
        return s_Window->ShouldClose();
    }

    void BeginFrame()
    {
        Input::UpdateState();
        glfwPollEvents();
    }

    void EndFrame()
    {
        glfwSwapBuffers(s_Window->GetHandle());
    }

    void Shutdown()
    {
        RVT_CORE_INFO("Rivet shutdown");
        s_Window.reset();
        glfwTerminate();
    }

    void SetClearColor(float r, float g, float b, float a)
    {
        s_ClearColor = { r, g, b, a };
    }

    void SetClearColor(const glm::vec4& color)
    {
        s_ClearColor = color;
    }

    void Clear()
    {
        glClearColor(s_ClearColor.r, s_ClearColor.g, s_ClearColor.b, s_ClearColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void SetViewport(int x, int y, int width, int height)
    {
        glViewport(x, y, width, height);
    }

    glm::ivec2 GetWindowSize()
    {
        return s_Window->GetWindowSize();
    }

}
