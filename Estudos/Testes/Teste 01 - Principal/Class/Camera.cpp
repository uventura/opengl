#include "Camera.h"

Camera::Camera() : m_Camera(1.0f), m_CameraPos(1.0f)
{
    m_CameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Camera::Move(float front, float back, float left, float right)
{
    float moveX = front - back;
    float moveY = right - left;

    glm::mat4 move(1.0f);
    move = glm::translate(m_Camera, glm::vec3(-moveX, -moveY, 0.0f));

    m_Camera *= move;
}

void Camera::Rotate(float up, float down, float left, float right)
{
    /* Arguments are in degrees. */

    float angleZ = left - right;
    float angleX = up - down;

    glm::mat4 rotate(1.0f);
    rotate = glm::rotate(rotate, glm::radians(angleZ), glm::vec3(0.0f, 0.0f, 1.0f);

    m_Camera *= rotate;
}

void Camera::Zoom(float view)
{
    glm::mat4 zoom(1.0f);
    zoom = glm::scale(zoom, glm::vec3(view, view, view));

    m_Camera *= zoom;
}

glm::mat4 Camera::Result()
{
    return m_Camera;
}