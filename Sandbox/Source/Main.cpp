#include <Rivet/Rivet.h>
#include <imgui.h>
#include <cmath>

int main()
{
    Rivet::Init("Sandbox — 2D Drawing", 1280, 720);
    Rivet::Editor::Init(Rivet::GetNativeWindow());
    Rivet::SetClearColor(0.15f, 0.15f, 0.20f, 1.0f);

    // ---- Renderer2D & texture -------------------------------------------
    Rivet::Renderer2D::Init();
    const Rivet::Texture2D* checker = Rivet::Assets::LoadTexture("assets/checker.png");

    // ---- Physics ------------------------------------------------------------
    constexpr float PPM = 80.0f;
    Rivet::Physics::Init({ 0.0f, -9.8f });
    auto groundBody = Rivet::Physics::AddStaticBody ({ 0.0f, -3.0f }, { 6.0f, 0.2f });
    auto boxA = Rivet::Physics::AddDynamicBody({ -1.0f,  5.0f }, { 0.4f, 0.4f });
    auto boxB = Rivet::Physics::AddDynamicBody({  1.0f,  8.0f }, { 0.4f, 0.4f });

    // ---- Audio ---------------------------------------------------------------
    Rivet::Audio::Sound* music  = Rivet::Assets::LoadSound("assets/audio/music.wav");
    Rivet::Audio::Sound* effect = Rivet::Assets::LoadSound("assets/audio/effect.wav");
    if (music)
    {
        Rivet::Audio::SetVolume(*music, 0.4f);
        Rivet::Audio::SetLoop(*music, true);
        Rivet::Audio::Play(*music);
    }
    float emitterAngle = 0.0f;
    constexpr float emitterRadius = 400.0f;

    // ---- Camera ---------------------------------------------------------
    Rivet::Camera2D camera{};
    const Rivet::Camera2D defaultCamera{};

    // ---- Sprite positions & tints ---------------------------------------
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

    // ---- UI setup -------------------------------------------------------
    Rivet::UI::Font uiFont = Rivet::UI::LoadFont("assets/fonts/font.ttf", 18.0f);

    // FPS panel (top-left)
    Rivet::UI::Panel fpsPanel;
    fpsPanel.position = { 8.0f, 8.0f };
    fpsPanel.size     = { 180.0f, 28.0f };
    fpsPanel.color    = { 0.10f, 0.10f, 0.10f, 0.80f };

    Rivet::UI::Label fpsLabel;
    fpsLabel.position = { 12.0f, 14.0f };
    fpsLabel.font     = &uiFont;
    fpsLabel.color    = { 0.9f, 0.9f, 0.3f, 1.0f };

    // Button
    Rivet::UI::Button demoButton;
    demoButton.panel.position = { 8.0f, 44.0f };
    demoButton.panel.size     = { 180.0f, 34.0f };
    demoButton.panel.color    = { 0.20f, 0.45f, 0.20f, 0.90f };
    demoButton.label.font     = &uiFont;
    demoButton.label.text     = "Click me!";
    demoButton.label.color    = { 1.0f, 1.0f, 1.0f, 1.0f };
    demoButton.onClick        = []() { RVT_INFO("Button clicked"); };

    // Health bar
    Rivet::UI::HealthBar healthBar;
    healthBar.position = { 8.0f, 86.0f };
    healthBar.size     = { 180.0f, 18.0f };
    healthBar.bgColor  = { 0.25f, 0.08f, 0.08f, 0.90f };
    healthBar.fgColor  = { 0.85f, 0.18f, 0.18f, 0.90f };

    // ---- Timing ---------------------------------------------------------
    double fpsTimer = glfwGetTime();
    int    fpsCount = 0;
    float  fps      = 0.0f;
    double lastTime = glfwGetTime();
    float  elapsed  = 0.0f;

    const float panSpeed  = 300.0f;
    const float zoomSpeed = 1.5f;

    while (!Rivet::ShouldClose())
    {
        double now   = glfwGetTime();
        float  delta = static_cast<float>(now - lastTime);
        lastTime     = now;
        elapsed     += delta;

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

        // ---- Audio update -----------------------------------------------
        emitterAngle += delta * 0.8f;
        float ex = emitterRadius * std::cos(emitterAngle);
        float ey = emitterRadius * std::sin(emitterAngle);
        Rivet::Audio::SetListenerPosition(0.0f, 0.0f);
        if (effect) Rivet::Audio::SetPosition(*effect, ex, ey);

        if (Rivet::IsKeyPressed(Rivet::Key::Space) && effect)
        {
            Rivet::Audio::SetVolume(*effect, 1.0f);
            Rivet::Audio::Play(*effect);
        }
        if (Rivet::IsKeyPressed(Rivet::Key::M) && music)
        {
            if (Rivet::Audio::IsPlaying(*music)) Rivet::Audio::Pause(*music);
            else                                 Rivet::Audio::Resume(*music);
        }

        // ---- Box A controls ---------------------------------------------
        constexpr float moveForce = 12.0f;
        glm::vec2 vel = { 0.0f, 0.0f };
        if (Rivet::IsKeyDown(Rivet::Key::Left))  vel.x -= moveForce;
        if (Rivet::IsKeyDown(Rivet::Key::Right)) vel.x += moveForce;
        if (Rivet::IsKeyPressed(Rivet::Key::Up)) vel.y  = moveForce * 2.5f;
        if (vel.x != 0.0f || vel.y != 0.0f)
            Rivet::Physics::ApplyImpulse(boxA, vel * delta);

        Rivet::Physics::Step(delta);

        // ---- UI update --------------------------------------------------
        glm::vec2 mousePos   = Rivet::GetMousePosition();
        bool      leftClick  = Rivet::IsMouseButtonPressed(Rivet::MouseButton::Left);

        fpsLabel.text    = "FPS: " + std::to_string(static_cast<int>(fps));
        healthBar.fill   = (std::sin(elapsed * 0.8f) * 0.5f + 0.5f);   // 0..1 sine wave
        Rivet::UI::UpdateButton(demoButton, mousePos, leftClick);

        // ---- Render -----------------------------------------------------
        Rivet::BeginFrame();
        Rivet::Clear();

        // World scene
        Rivet::BeginCamera2D(camera);
        Rivet::Renderer2D::BeginScene();
        for (int i = 0; i < SpriteCount; ++i)
            Rivet::Renderer2D::DrawTexture(*checker, positions[i], spriteSize, tints[i]);
        {
            glm::vec2 gPos = Rivet::Physics::GetPosition(groundBody) * PPM;
            Rivet::Renderer2D::DrawQuad(gPos, { 6.0f * 2.0f * PPM, 0.2f * 2.0f * PPM },
                                        { 0.55f, 0.45f, 0.35f, 1.0f });
            glm::vec2 aPos = Rivet::Physics::GetPosition(boxA) * PPM;
            Rivet::Renderer2D::DrawQuad(aPos, { 0.4f * 2.0f * PPM, 0.4f * 2.0f * PPM },
                                        { 0.9f, 0.3f, 0.3f, 1.0f });
            glm::vec2 bPos = Rivet::Physics::GetPosition(boxB) * PPM;
            Rivet::Renderer2D::DrawQuad(bPos, { 0.4f * 2.0f * PPM, 0.4f * 2.0f * PPM },
                                        { 0.3f, 0.6f, 0.9f, 1.0f });
        }
        Rivet::Renderer2D::EndScene();
        Rivet::EndCamera2D();

        // In-game UI (screen space, rendered over the world)
        Rivet::UI::BeginScene();
        Rivet::UI::DrawPanel(fpsPanel);
        Rivet::UI::DrawLabel(fpsLabel);
        Rivet::UI::DrawButton(demoButton);
        Rivet::UI::DrawHealthBar(healthBar);
        Rivet::UI::EndScene();

        // Debug overlay (ImGui)
        Rivet::Editor::Begin();
        ImGui::SetNextWindowPos(ImVec2(10, 120), ImGuiCond_Always);
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
        ImGui::Text("Music: %s", (music && Rivet::Audio::IsPlaying(*music)) ? "playing" : "paused");
        ImGui::Text("Emitter: (%.0f, %.0f)", ex, ey);
        ImGui::Separator();
        ImGui::TextDisabled("WASD=pan  Q/E=zoom  R=reset");
        ImGui::TextDisabled("Arrows=move red box  Up=jump");
        ImGui::TextDisabled("Space=effect  M=toggle music");
        ImGui::End();
        Rivet::Editor::End();

        Rivet::EndFrame();
    }

    Rivet::UI::UnloadFont(uiFont);
    Rivet::Assets::UnloadAllTextures();
    Rivet::Assets::UnloadAllShaders();
    Rivet::Assets::UnloadAllSounds();
    Rivet::Physics::Shutdown();
    Rivet::Renderer2D::Shutdown();
    Rivet::Editor::Shutdown();
    Rivet::Shutdown();

    return 0;
}
