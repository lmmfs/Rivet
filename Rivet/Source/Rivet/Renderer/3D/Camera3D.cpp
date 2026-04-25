#include "Camera3D.h"
#include "../../Core/Input.h"

#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include <cmath>

namespace Rivet {

static constexpr float k_PitchMin  =  0.01f;   // just above the horizon
static constexpr float k_PitchMax  =  1.55f;   // just below vertical
static constexpr float k_RadiusMin =  0.5f;
static constexpr float k_RadiusMax = 50.0f;

glm::vec3 GetCameraEye(const Camera3D& cam)
{
    return {
        cam.target.x + cam.radius * std::cos(cam.pitch) * std::sin(cam.yaw),
        cam.target.y + cam.radius * std::sin(cam.pitch),
        cam.target.z + cam.radius * std::cos(cam.pitch) * std::cos(cam.yaw)
    };
}

glm::mat4 GetViewMatrix(const Camera3D& cam)
{
    return glm::lookAt(GetCameraEye(cam), cam.target, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 GetProjectionMatrix(const Camera3D& cam, float aspectRatio)
{
    return glm::perspective(glm::radians(cam.fov), aspectRatio, cam.nearZ, cam.farZ);
}

void OrbitCameraUpdate(Camera3D& cam, float mouseSensitivity, float scrollSensitivity)
{
    if (IsMouseButtonDown(MouseButton::Left))
    {
        glm::vec2 delta = GetMouseDelta();
        cam.yaw   += delta.x * mouseSensitivity;
        cam.pitch -= delta.y * mouseSensitivity;   // invert Y: drag up → look up
        cam.pitch  = std::clamp(cam.pitch, k_PitchMin, k_PitchMax);
    }

    float scroll = GetMouseScroll();
    cam.radius  -= scroll * scrollSensitivity;
    cam.radius   = std::clamp(cam.radius, k_RadiusMin, k_RadiusMax);
}

} // namespace Rivet
