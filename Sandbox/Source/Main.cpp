#include <Rivet/Rivet.h>

int main()
{
    Rivet::Init("Sandbox", 1280, 720);
    Rivet::Editor::Init(Rivet::GetNativeWindow());
    Rivet::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    Rivet::Shader shader = Rivet::LoadShader("shaders/basic.vert", "shaders/basic.frag");

    float positions[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    float colors[] = {
        1.0f, 0.0f, 0.0f,   // bottom-left  — red
        1.0f, 1.0f, 1.0f,   // bottom-right — green
        0.0f, 0.0f, 1.0f,   // top          — blue
    };

    Rivet::VertexArray  va    = Rivet::CreateVertexArray();
    Rivet::VertexBuffer vbPos = Rivet::CreateVertexBuffer(positions, sizeof(positions));
    Rivet::VertexBuffer vbCol = Rivet::CreateVertexBuffer(colors,    sizeof(colors));

    Rivet::BufferLayout posLayout = { { Rivet::ShaderDataType::Float3, "a_Position" } };
    Rivet::BufferLayout colLayout = { { Rivet::ShaderDataType::Float3, "a_Color"    } };

    Rivet::SetVertexArrayLayout(va, vbPos, posLayout);
    Rivet::SetVertexArrayLayout(va, vbCol, colLayout);

    uint64_t frame    = 0;
    double   fpsTimer = glfwGetTime();
    int      fpsCount = 0;

    while (!Rivet::ShouldClose())
    {
        Rivet::BeginFrame();
        Rivet::Clear();

        // FPS counter — log once per second
        ++fpsCount;
        double now = glfwGetTime();
        if (now - fpsTimer >= 1.0)
        {
            RVT_INFO("FPS: {}", fpsCount);
            fpsCount  = 0;
            fpsTimer += 1.0;
        }

        // Drain the event queue
        Rivet::Event e;
        while (Rivet::PollEvent(e))
        {
            switch (e.type)
            {
                case Rivet::EventType::WindowClose:
                    RVT_INFO("[Event] WindowClose");
                    break;
                case Rivet::EventType::WindowResize:
                    RVT_INFO("[Event] WindowResize: {}x{}", e.windowResize.width, e.windowResize.height);
                    break;
                case Rivet::EventType::WindowFocus:
                    RVT_INFO("[Event] WindowFocus");
                    break;
                case Rivet::EventType::WindowLostFocus:
                    RVT_INFO("[Event] WindowLostFocus");
                    break;
                case Rivet::EventType::KeyPressed:
                    RVT_INFO("[Event] KeyPressed: key={} repeat={}", static_cast<int>(e.keyPressed.key), e.keyPressed.repeatCount);
                    break;
                case Rivet::EventType::KeyReleased:
                    RVT_INFO("[Event] KeyReleased: key={}", static_cast<int>(e.keyReleased.key));
                    break;
                case Rivet::EventType::MouseMoved:
                    RVT_DEBUG("[Event] MouseMoved: ({:.1f}, {:.1f})", e.mouseMoved.x, e.mouseMoved.y);
                    break;
                case Rivet::EventType::MouseScrolled:
                    RVT_INFO("[Event] MouseScrolled: ({:.2f}, {:.2f})", e.mouseScrolled.xOffset, e.mouseScrolled.yOffset);
                    break;
                case Rivet::EventType::MouseButtonPressed:
                    RVT_INFO("[Event] MouseButtonPressed: button={}", static_cast<int>(e.mouseButton.button));
                    break;
                case Rivet::EventType::MouseButtonReleased:
                    RVT_INFO("[Event] MouseButtonReleased: button={}", static_cast<int>(e.mouseButton.button));
                    break;
                default: break;
            }
        }

        if (Rivet::IsKeyPressed(Rivet::Key::Escape))
            break;

        // Draw triangle
        Rivet::UseShader(shader);
        Rivet::BindVertexArray(va);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        Rivet::Editor::Begin();
        ImGui::ShowDemoWindow();
        Rivet::Editor::End();

        Rivet::EndFrame();
    }

    Rivet::DeleteVertexArray(va);
    Rivet::DeleteVertexBuffer(vbPos);
    Rivet::DeleteVertexBuffer(vbCol);
    Rivet::DeleteShader(shader);

    Rivet::Editor::Shutdown();
    Rivet::Shutdown();

    return 0;
}

