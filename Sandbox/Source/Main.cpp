#include <Rivet/Rivet.h>

int main()
{
    Rivet::WindowSpecification spec;
    spec.Title = "Sandbox";
    spec.Width = 1280;
    spec.Height = 720;

    Rivet::Window window(spec);
    window.Create();

    while (!window.ShouldClose())
    {
        window.Update();
    }

    window.Destroy();

    return 0;
}
