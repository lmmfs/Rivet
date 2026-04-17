#include <Rivet/Rivet.h>

int main()
{
    Rivet::Init("Sandboxx", 1280, 720);
    Rivet::SetClearColor(0.53f, 0.81f, 0.92f);

    while (!Rivet::ShouldClose())
    {
        Rivet::BeginFrame();

        if (Rivet::IsKeyPressed(Rivet::Key::Escape))
            break;

        RVT_INFO("Mouse: ({:.1f}, {:.1f})", Rivet::GetMousePosition().x, Rivet::GetMousePosition().y);

        Rivet::EndFrame();
    }

    Rivet::Shutdown();

    return 0;
}

