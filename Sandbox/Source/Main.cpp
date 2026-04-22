#include <Rivet/Rivet.h>
#include <imgui.h>

int main()
{
    Rivet::Init("Sandbox — 2D Drawing", 1280, 720);
    Rivet::Editor::Init(Rivet::GetNativeWindow());
    Rivet::SetClearColor(0.15f, 0.15f, 0.20f, 1.0f);

    // ---- Renderer2D & texture -------------------------------------------
    Rivet::Renderer2D::Init();
    const Rivet::Texture2D* checker = Rivet::Assets::LoadTexture("assets/checker.png");

    // ---- Camera ---------------------------------------------------------
    Rivet::Camera2D camera{};
    const Rivet::Camera2D defaultCamera{};

    // ---- Sprite positions & tints (world space) -------------------------
    const glm::vec2 spriteSize{ 128.0f, 128.0f };
    const glm::vec4 tints[] = {
        { 1.0f, 1.0f, 1.0f, 1.0f },
        { 1.0f, 0.4f, 0.4f, 1.0f },
        { 0.4f, 1.0f, 0.4f, 1.0f },
        { 0.6f, 0.6f, 0.2f, 1.0f },
        { 1.0f, 0.3f, 0.4f, 1.0f },
    };
    const glm::vec2 positions[] = {
        {   0.0f,   0.0f },
        { 160.0f,   0.0f },
        {-160.0f,   0.0f },
        {   0.0f, 160.0f },
        {   0.0f,-160.0f },
    };
    constexpr int SpriteCount = 5;

    // ---- Timing ---------------------------------------------------------
    double fpsTimer = glfwGetTime();
    int    fpsCount = 0;
    float  fps      = 0.0f;
    double lastTime = glfwGetTime();

    const float panSpeed  = 300.0f;
    const float zoomSpeed = 1.5f;

    while (!Rivet::ShouldClose())
    {
        // ---- Delta time -------------------------------------------------
        double now   = glfwGetTime();
        float  delta = static_cast<float>(now - lastTime);
        lastTime     = now;

        // ---- FPS --------------------------------------------------------
        ++fpsCount;
        if (now - fpsTimer >= 1.0)
        {
            fps      = static_cast<float>(fpsCount) / static_cast<float>(now - fpsTimer);
            fpsCount = 0;
            fpsTimer = now;
        }

        // ---- Camera input -----------------------------------------------
        if (Rivet::IsKeyDown(Rivet::Key::W)) camera.position.y += panSpeed * delta;
        if (Rivet::IsKeyDown(Rivet::Key::S)) camera.position.y -= panSpeed * delta;
        if (Rivet::IsKeyDown(Rivet::Key::A)) camera.position.x -= panSpeed * delta;
        if (Rivet::IsKeyDown(Rivet::Key::D)) camera.position.x += panSpeed * delta;
        if (Rivet::IsKeyDown(Rivet::Key::Q)) camera.zoom *= 1.0f + zoomSpeed * delta;
        if (Rivet::IsKeyDown(Rivet::Key::E)) camera.zoom /= 1.0f + zoomSpeed * delta;
        if (Rivet::IsKeyPressed(Rivet::Key::R)) camera = defaultCamera;
        if (camera.zoom < 0.05f) camera.zoom = 0.05f;
        if (camera.zoom > 20.0f) camera.zoom = 20.0f;

        // ---- Events -----------------------------------------------------
        Rivet::Event e;
        while (Rivet::PollEvent(e))
        {
            if (e.type == Rivet::EventType::WindowResize)
                Rivet::SetViewport(0, 0, e.windowResize.width, e.windowResize.height);
        }

        if (Rivet::IsKeyPressed(Rivet::Key::Escape))
            break;

        // ---- Render -----------------------------------------------------
        Rivet::BeginFrame();
        Rivet::Clear();

        Rivet::BeginCamera2D(camera);
        Rivet::Renderer2D::BeginScene();
        for (int i = 0; i < SpriteCount; ++i)
            Rivet::Renderer2D::DrawTexture(*checker, positions[i], spriteSize, tints[i]);
        Rivet::Renderer2D::EndScene();
        Rivet::EndCamera2D();

        // ---- ImGui overlay ----------------------------------------------
        Rivet::Editor::Begin();
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
        ImGui::SetNextWindowBgAlpha(0.6f);
        ImGui::Begin("Camera", nullptr,
                     ImGuiWindowFlags_NoDecoration |
                     ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoSavedSettings);
        ImGui::Text("FPS:  %.1f", fps);
        ImGui::Separator();
        ImGui::Text("Pos:  (%.1f, %.1f)", camera.position.x, camera.position.y);
        ImGui::Text("Zoom: %.3f", camera.zoom);
        ImGui::Separator();
        ImGui::TextDisabled("WASD=pan  Q/E=zoom  R=reset");
        ImGui::End();
        Rivet::Editor::End();

        Rivet::EndFrame();
    }

    Rivet::Assets::UnloadAllTextures();
    Rivet::Assets::UnloadAllShaders();
    Rivet::Renderer2D::Shutdown();
    Rivet::Editor::Shutdown();
    Rivet::Shutdown();

    return 0;
}

