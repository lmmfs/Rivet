
#include "Window.h"
#include "App.h"
#include "Logger.h"
#include "Events/EventQueue.h"

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

        // ---- Window events ----

        glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow*)
        {
            Event e;
            e.type = EventType::WindowClose;
            PushEvent(e);
        });

        // Update the GL viewport AND push the resize event.
        // Using glfwGetFramebufferSize gives pixel dimensions (correct on HiDPI too).
        glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height)
        {
            int fbw, fbh;
            glfwGetFramebufferSize(window, &fbw, &fbh);
            SetViewport(0, 0, fbw, fbh);

            Event e;
            e.type = EventType::WindowResize;
            e.windowResize.width  = width;
            e.windowResize.height = height;
            PushEvent(e);
        });

        glfwSetWindowFocusCallback(m_Handle, [](GLFWwindow*, int focused)
        {
            Event e;
            e.type = focused ? EventType::WindowFocus : EventType::WindowLostFocus;
            PushEvent(e);
        });

        // ---- Input events ----

        glfwSetKeyCallback(m_Handle, [](GLFWwindow*, int key, int /*scancode*/, int action, int /*mods*/)
        {
            if (action == GLFW_PRESS || action == GLFW_REPEAT)
            {
                Event e;
                e.type = EventType::KeyPressed;
                e.keyPressed.key         = static_cast<Key>(key);
                e.keyPressed.repeatCount = (action == GLFW_REPEAT) ? 1 : 0;
                PushEvent(e);
            }
            else if (action == GLFW_RELEASE)
            {
                Event e;
                e.type = EventType::KeyReleased;
                e.keyReleased.key = static_cast<Key>(key);
                PushEvent(e);
            }
        });

        glfwSetCursorPosCallback(m_Handle, [](GLFWwindow*, double x, double y)
        {
            Event e;
            e.type       = EventType::MouseMoved;
            e.mouseMoved.x = static_cast<float>(x);
            e.mouseMoved.y = static_cast<float>(y);
            PushEvent(e);
        });

        glfwSetScrollCallback(m_Handle, [](GLFWwindow*, double xOffset, double yOffset)
        {
            Event e;
            e.type = EventType::MouseScrolled;
            e.mouseScrolled.xOffset = static_cast<float>(xOffset);
            e.mouseScrolled.yOffset = static_cast<float>(yOffset);
            PushEvent(e);
        });

        glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow*, int button, int action, int /*mods*/)
        {
            Event e;
            e.type         = (action == GLFW_PRESS) ? EventType::MouseButtonPressed
                                                     : EventType::MouseButtonReleased;
            e.mouseButton.button = static_cast<MouseButton>(button);
            PushEvent(e);
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
