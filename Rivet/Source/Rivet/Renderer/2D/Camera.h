#pragma once

#include <glm/glm.hpp>

namespace Rivet {

    struct Camera2D
    {
        glm::vec2 position = { 0.0f, 0.0f };
        float     zoom     = 1.0f;
        float     rotation = 0.0f;   // degrees
    };

    // Returns the combined view-projection matrix for a 2D orthographic camera.
    // Uses the current window size as the viewport extent.
    glm::mat4 GetCamera2DMatrix(const Camera2D& cam);

    // Push the camera's VP matrix into the Renderer2D state.
    // Must be called before DrawTexture calls within a scene.
    void BeginCamera2D(const Camera2D& cam);
    void EndCamera2D();

} // namespace Rivet
