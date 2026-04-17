#include "Input.h"

#include <array>

namespace {

    GLFWwindow* s_Handle = nullptr;

    std::array<int, GLFW_KEY_LAST + 1>          s_CurrentKeys{};
    std::array<int, GLFW_KEY_LAST + 1>          s_PreviousKeys{};

    std::array<int, GLFW_MOUSE_BUTTON_LAST + 1> s_CurrentMouseButtons{};
    std::array<int, GLFW_MOUSE_BUTTON_LAST + 1> s_PreviousMouseButtons{};

    glm::vec2 s_CurrentMousePos{};
    glm::vec2 s_PreviousMousePos{};

}

namespace Rivet::Input {

    void Init(GLFWwindow* handle)
    {
        s_Handle = handle;
    }

    void UpdateState()
    {
        // Snapshot previous frame
        s_PreviousKeys         = s_CurrentKeys;
        s_PreviousMouseButtons = s_CurrentMouseButtons;
        s_PreviousMousePos     = s_CurrentMousePos;

        // Sample current keyboard state
        for (int i = 0; i <= GLFW_KEY_LAST; ++i)
            s_CurrentKeys[i] = glfwGetKey(s_Handle, i);

        // Sample current mouse button state
        for (int i = 0; i <= GLFW_MOUSE_BUTTON_LAST; ++i)
            s_CurrentMouseButtons[i] = glfwGetMouseButton(s_Handle, i);

        // Sample cursor position
        double x = 0.0, y = 0.0;
        glfwGetCursorPos(s_Handle, &x, &y);
        s_CurrentMousePos = { static_cast<float>(x), static_cast<float>(y) };
    }

}

namespace Rivet {

    // ---- Keyboard ----

    bool IsKeyDown(Key key)
    {
        int k = static_cast<int>(key);
        if (k < 0 || k > GLFW_KEY_LAST) return false;
        return s_CurrentKeys[k] == GLFW_PRESS;
    }

    bool IsKeyPressed(Key key)
    {
        int k = static_cast<int>(key);
        if (k < 0 || k > GLFW_KEY_LAST) return false;
        return s_CurrentKeys[k] == GLFW_PRESS && s_PreviousKeys[k] != GLFW_PRESS;
    }

    bool IsKeyReleased(Key key)
    {
        int k = static_cast<int>(key);
        if (k < 0 || k > GLFW_KEY_LAST) return false;
        return s_CurrentKeys[k] != GLFW_PRESS && s_PreviousKeys[k] == GLFW_PRESS;
    }

    // ---- Mouse ----

    glm::vec2 GetMousePosition()
    {
        return s_CurrentMousePos;
    }

    glm::vec2 GetMouseDelta()
    {
        return s_CurrentMousePos - s_PreviousMousePos;
    }

    bool IsMouseButtonDown(MouseButton btn)
    {
        int b = static_cast<int>(btn);
        if (b < 0 || b > GLFW_MOUSE_BUTTON_LAST) return false;
        return s_CurrentMouseButtons[b] == GLFW_PRESS;
    }

    bool IsMouseButtonPressed(MouseButton btn)
    {
        int b = static_cast<int>(btn);
        if (b < 0 || b > GLFW_MOUSE_BUTTON_LAST) return false;
        return s_CurrentMouseButtons[b] == GLFW_PRESS && s_PreviousMouseButtons[b] != GLFW_PRESS;
    }

    bool IsMouseButtonReleased(MouseButton btn)
    {
        int b = static_cast<int>(btn);
        if (b < 0 || b > GLFW_MOUSE_BUTTON_LAST) return false;
        return s_CurrentMouseButtons[b] != GLFW_PRESS && s_PreviousMouseButtons[b] == GLFW_PRESS;
    }

}
