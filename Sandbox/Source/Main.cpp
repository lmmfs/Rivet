#include <Rivet/Rivet.h>

int main()
{
    Rivet::Init("Sandboxx", 1280, 720);
    Rivet::SetClearColor(0.53f, 0.81f, 0.92f);

    uint64_t frame = 0;

    while (!Rivet::ShouldClose())
    {
        Rivet::BeginFrame();

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

