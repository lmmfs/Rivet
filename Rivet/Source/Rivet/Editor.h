#pragma once

#include <imgui.h>

struct GLFWwindow;

namespace Rivet::Editor {

    void Init(GLFWwindow* window);
    void Shutdown();

    void Begin();
    void End();

}
