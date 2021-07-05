#include "Camera.h"

Camera3D::Camera3D()
{
    m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    m_cameraZoom = 45.0f;
    m_cameraSpeed = 0.13f;
}

void Camera3D::moveCamera(bool* cam_keys)
{
    if(cam_keys[GLFW_KEY_W] || cam_keys[GLFW_KEY_UP])
        m_cameraPos += m_cameraFront * m_cameraSpeed;
    if(cam_keys[GLFW_KEY_S] || cam_keys[GLFW_KEY_DOWN])
        m_cameraPos -= m_cameraFront * m_cameraSpeed;
    if(cam_keys[GLFW_KEY_A] || cam_keys[GLFW_KEY_LEFT])
        m_cameraPos += glm::normalize(glm::cross(m_cameraUp, m_cameraFront)) * m_cameraSpeed;
    if(cam_keys[GLFW_KEY_D] || cam_keys[GLFW_KEY_RIGHT])
        m_cameraPos -= glm::normalize(glm::cross(m_cameraUp, m_cameraFront)) * m_cameraSpeed;
}

void Camera3D::setZoom(float zoom)
{
    m_cameraZoom = zoom;

    if(zoom < 10.0f)
        zoom = 10.0f;
    else if(zoom > 45.0f)
        zoom = 45.0f;
};