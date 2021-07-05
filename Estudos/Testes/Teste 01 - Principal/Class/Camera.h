#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
    glm::mat4 m_Camera;
    glm::vec3 m_CameraPos;
    glm::vec3 m_CameraTarget;

public:
    Camera();

    void Move(float front, float back, float left, float right);
    void Rotate(float up, float down, float left, float right);
    void Zoom(float view);

    glm::mat4 Result();
};