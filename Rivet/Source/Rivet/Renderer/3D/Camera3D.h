#pragma once

#include <glm/glm.hpp>

namespace Rivet {

    // -------------------------------------------------------------------------
    // Camera3D — perspective camera with orbit (arcball) controller
    // -------------------------------------------------------------------------

    struct Camera3D
    {
        glm::vec3 target = { 0.0f, 0.0f, 0.0f }; // point being orbited
        float     yaw    = 0.0f;    // horizontal angle (radians)
        float     pitch  = 0.3f;    // vertical angle   (radians)
        float     radius = 5.0f;    // distance from target
        float     fov    = 45.0f;   // vertical field of view (degrees)
        float     nearZ  = 0.1f;
        float     farZ   = 100.0f;
    };

    // Compute the eye position from orbit parameters
    glm::vec3 GetCameraEye(const Camera3D& cam);

    // View matrix (lookAt from eye toward target, up = world Y)
    glm::mat4 GetViewMatrix(const Camera3D& cam);

    // Perspective projection matrix
    glm::mat4 GetProjectionMatrix(const Camera3D& cam, float aspectRatio);

    // Read mouse input and update yaw / pitch / radius.  Call once per frame.
    // Left-mouse drag rotates; scroll wheel zooms.
    void OrbitCameraUpdate(Camera3D& cam,
                           float mouseSensitivity  = 0.005f,
                           float scrollSensitivity = 0.5f);

} // namespace Rivet
