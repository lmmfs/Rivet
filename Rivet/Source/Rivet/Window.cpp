
#include "Window.h"


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
            std::cerr << "Failed to initialize GLFW" << std::endl;
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
            //CORE_ERROR("Failed to create GLFW window");
            std::cerr << "Failed to create GLFW window" << std::endl;
            assert(false);
        }

        //glfwSetWindowUserPointer(m_Handle, this);

        glfwMakeContextCurrent(m_Handle);
        glfwSetWindowUserPointer(m_Handle, &m_Specification);
        gladLoadGL(glfwGetProcAddress);

        glfwSwapInterval(m_Specification.VSync ? 1 : 0);


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

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Handle) != 0;
    }

}
