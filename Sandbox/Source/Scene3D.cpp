#include "Scene3D.h"

#include <Rivet/Rivet.h>
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

void RunScene3D()
{
    Rivet::Init("Sandbox — 3D Renderer", 1280, 720);
    Rivet::Editor::Init(Rivet::GetNativeWindow());
    Rivet::SetClearColor(0.10f, 0.12f, 0.18f, 1.0f);

    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);

    // ---- Shader ---------------------------------------------------------
    Rivet::Shader shader3d = Rivet::LoadShader("shaders/basic3d.vert",
                                               "shaders/basic3d.frag");

    // ---- Geometry -------------------------------------------------------
    Rivet::Mesh cubeMesh = Rivet::CreateCubeMesh();

    // ---- Texture (reuse 2D asset) ----------------------------------------
    Rivet::Texture2D* checker = Rivet::Assets::LoadTexture("assets/checker.png");

    // ---- Camera ---------------------------------------------------------
    Rivet::Camera3D cam;
    cam.target = { 0.0f, 0.0f, 0.0f };
    cam.radius = 3.5f;
    cam.pitch  = 0.4f;
    cam.fov    = 45.0f;

    // ---- UI -------------------------------------------------------------
    Rivet::UI::Font uiFont = Rivet::UI::LoadFont("assets/fonts/font.ttf", 18.0f);

    Rivet::UI::Panel fpsPanel;
    fpsPanel.position = { 8.0f, 8.0f };
    fpsPanel.size     = { 190.0f, 28.0f };
    fpsPanel.color    = { 0.10f, 0.10f, 0.10f, 0.80f };

    Rivet::UI::Label fpsLabel;
    fpsLabel.position = { 12.0f, 14.0f };
    fpsLabel.font     = &uiFont;
    fpsLabel.color    = { 0.9f, 0.9f, 0.3f, 1.0f };

    // ---- Timing ---------------------------------------------------------
    double fpsTimer = glfwGetTime();
    int    fpsCount = 0;
    float  fps      = 0.0f;
    double lastTime = glfwGetTime();
    float  rotation = 0.0f;   // cube spin angle (degrees)

    glm::ivec2 winSize = Rivet::GetWindowSize();
    float aspect = static_cast<float>(winSize.x) / static_cast<float>(winSize.y);

    while (!Rivet::ShouldClose())
    {
        double now   = glfwGetTime();
        float  delta = static_cast<float>(now - lastTime);
        lastTime     = now;

        ++fpsCount;
        if (now - fpsTimer >= 1.0)
        {
            fps      = static_cast<float>(fpsCount) / static_cast<float>(now - fpsTimer);
            fpsCount = 0;
            fpsTimer = now;
        }

        // ---- Events -----------------------------------------------------
        Rivet::Event e;
        while (Rivet::PollEvent(e))
        {
            if (e.type == Rivet::EventType::WindowResize)
            {
                Rivet::SetViewport(0, 0, e.windowResize.width, e.windowResize.height);
                aspect = static_cast<float>(e.windowResize.width) /
                         static_cast<float>(e.windowResize.height);
            }
        }

        if (Rivet::IsKeyPressed(Rivet::Key::Escape))
            break;

        // ---- Camera orbit -----------------------------------------------
        Rivet::OrbitCameraUpdate(cam);

        // ---- Spin cube --------------------------------------------------
        rotation += delta * 45.0f;   // 45 degrees per second

        // ---- Matrices ---------------------------------------------------
        glm::mat4 model = glm::rotate(glm::mat4(1.0f),
                                      glm::radians(rotation),
                                      glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 view       = Rivet::GetViewMatrix(cam);
        glm::mat4 projection = Rivet::GetProjectionMatrix(cam, aspect);

        // ---- UI update --------------------------------------------------
        fpsLabel.text = "FPS: " + std::to_string(static_cast<int>(fps));

        // ---- Render -----------------------------------------------------
        Rivet::BeginFrame();
        Rivet::Clear();

        // 3D draw
        Rivet::UseShader(shader3d);
        Rivet::SetUniformMat4(shader3d, "u_Model",      model);
        Rivet::SetUniformMat4(shader3d, "u_View",       view);
        Rivet::SetUniformMat4(shader3d, "u_Projection", projection);
        Rivet::SetUniformInt (shader3d, "u_Texture",    0);

        if (checker)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, checker->id);
        }
        Rivet::DrawMesh(cubeMesh);

        // UI overlay
        Rivet::UI::BeginScene();
        Rivet::UI::DrawPanel(fpsPanel);
        Rivet::UI::DrawLabel(fpsLabel);
        Rivet::UI::EndScene();

        // ImGui debug overlay
        Rivet::Editor::Begin();
        ImGui::SetNextWindowPos(ImVec2(10, 50), ImGuiCond_Always);
        ImGui::SetNextWindowBgAlpha(0.6f);
        ImGui::Begin("Camera 3D", nullptr,
                     ImGuiWindowFlags_NoDecoration |
                     ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoSavedSettings);
        glm::vec3 eye = Rivet::GetCameraEye(cam);
        ImGui::Text("FPS:    %.1f", fps);
        ImGui::Separator();
        ImGui::Text("Eye:    (%.2f, %.2f, %.2f)", eye.x, eye.y, eye.z);
        ImGui::Text("Yaw:    %.2f rad", cam.yaw);
        ImGui::Text("Pitch:  %.2f rad", cam.pitch);
        ImGui::Text("Radius: %.2f", cam.radius);
        ImGui::Separator();
        ImGui::TextDisabled("LMB drag = orbit");
        ImGui::TextDisabled("Scroll   = zoom");
        ImGui::TextDisabled("Esc      = quit");
        ImGui::End();
        Rivet::Editor::End();

        Rivet::EndFrame();
    }

    // ---- Cleanup --------------------------------------------------------
    Rivet::UI::UnloadFont(uiFont);
    Rivet::Assets::UnloadAllTextures();
    Rivet::Assets::UnloadAllShaders();
    Rivet::DeleteMesh(cubeMesh);
    Rivet::DeleteShader(shader3d);
    Rivet::Editor::Shutdown();
    Rivet::Shutdown();
}
