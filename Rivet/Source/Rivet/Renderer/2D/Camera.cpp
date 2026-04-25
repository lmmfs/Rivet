#include "Camera.h"
#include "Renderer.h"
#include "../../Core/App.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Rivet {

    glm::mat4 GetCamera2DMatrix(const Camera2D& cam)
    {
        glm::ivec2 size = GetWindowSize();
        float halfW = (size.x * 0.5f) / cam.zoom;
        float halfH = (size.y * 0.5f) / cam.zoom;

        glm::mat4 proj = glm::ortho(-halfW, halfW, -halfH, halfH, -1.0f, 1.0f);

        glm::mat4 view = glm::translate(glm::mat4(1.0f),
                                        glm::vec3(-cam.position, 0.0f));
        if (cam.rotation != 0.0f)
        {
            view = glm::rotate(view, glm::radians(cam.rotation),
                               glm::vec3(0.0f, 0.0f, 1.0f));
        }

        return proj * view;
    }

    void BeginCamera2D(const Camera2D& cam)
    {
        Renderer2D::SetViewProjection(GetCamera2DMatrix(cam));
    }

    void EndCamera2D()
    {
        Renderer2D::SetViewProjection(glm::mat4(1.0f));
    }

} // namespace Rivet
