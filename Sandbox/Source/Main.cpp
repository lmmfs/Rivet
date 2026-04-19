#include <Rivet/Rivet.h>

int main()
{
    Rivet::Init("Sandboxx", 1280, 720);
    Rivet::SetClearColor(0.53f, 0.81f, 0.92f);

    uint64_t frame = 0;

    while (!Rivet::ShouldClose())
    {
        Rivet::BeginFrame();

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

        // Validation 2: frame counter
        RVT_DEBUG("Frame {}", frame++);

        // Validation 3: keyboard
        if (Rivet::IsKeyDown(Rivet::Key::W))
            RVT_INFO("W down");
        if (Rivet::IsKeyPressed(Rivet::Key::W))
            RVT_INFO("W pressed (frame {})", frame);
        if (Rivet::IsKeyReleased(Rivet::Key::W))
            RVT_INFO("W released (frame {})", frame);

        // Validation 4: mouse
        RVT_DEBUG("Mouse pos: ({:.1f}, {:.1f})  delta: ({:.2f}, {:.2f})",
            Rivet::GetMousePosition().x, Rivet::GetMousePosition().y,
            Rivet::GetMouseDelta().x,    Rivet::GetMouseDelta().y);

        if (Rivet::IsMouseButtonDown(Rivet::MouseButton::Left))
            RVT_INFO("LMB down");
        if (Rivet::IsMouseButtonPressed(Rivet::MouseButton::Left))
            RVT_INFO("LMB pressed (frame {})", frame);
        if (Rivet::IsMouseButtonReleased(Rivet::MouseButton::Left))
            RVT_INFO("LMB released (frame {})", frame);

        Rivet::EndFrame();
    }

    Rivet::Shutdown();

    return 0;
}

