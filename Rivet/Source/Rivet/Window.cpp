
#include "Window.h"
#include "Logger.h"


#include "Rvtph.h"



namespace Rivet {

    Window::Window(const WindowSpecification& specification)
    : m_Specification(specification)
    {
    }

    Window::~Window()
    {
        Destroy();
    }

    void Window::Create()
    {
        if (!glfwInit())
        {
            RVT_CORE_ERROR("Failed to initialize GLFW");
            assert(false);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        m_Handle = glfwCreateWindow(m_Specification.Width, m_Specification.Height,
                                    m_Specification.Title.c_str(), nullptr, nullptr);

        if (!m_Handle)
        {
            RVT_CORE_ERROR("Failed to create GLFW window");
            assert(false);
        }

        glfwMakeContextCurrent(m_Handle);
        glfwSetWindowUserPointer(m_Handle, &m_Specification);
        gladLoadGL(glfwGetProcAddress);

        glfwSwapInterval(m_Specification.VSync ? 1 : 0);

        glfwSetFramebufferSizeCallback(m_Handle, [](GLFWwindow*, int width, int height)
        {
            glViewport(0, 0, width, height);
        });
    }

    void Window::Destroy()
    {
        if (m_Handle)
            glfwDestroyWindow(m_Handle);

        m_Handle = nullptr;
    }

    void Window::Update()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Handle);
    }

    glm::vec2 Window::GetFramebufferSize()
    {
        int width, height;
        glfwGetFramebufferSize(m_Handle, &width, &height);
        return { width, height };
    }

    glm::ivec2 Window::GetWindowSize()
    {
        int width, height;
        glfwGetFramebufferSize(m_Handle, &width, &height);
        return { width, height };
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Handle) != 0;
    }

}
