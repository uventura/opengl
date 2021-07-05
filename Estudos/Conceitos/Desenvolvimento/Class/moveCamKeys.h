#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Utilização do cursor
bool modeCursor = false;

// Transladação de Câmera
bool keys[1024];

// Zoom
float incrZoom = 45.0f;

// Rotação de Câmera
bool firstMove = true;
float pitch = 0.0f, yaw = 0.0f;
float xPrev = 320, yPrev = 240;
glm::vec3 frontDir(1.0f);

void keyCamCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);

    if(key == GLFW_KEY_C && action == GLFW_PRESS)
        modeCursor = !modeCursor;
};

void scrollCamCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    incrZoom -= yoffset;
}

void cursorCamCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(firstMove)
    {
        xPrev = xoffset;
        yPrev = yoffset;
        firstMove = false;
    }

    float sensitivity = 0.08f;
    float deltaX = xoffset - xPrev;
    float deltaY = yPrev - yoffset;

    xPrev = xoffset;
    yPrev = yoffset;

    pitch += (deltaY * sensitivity);
    yaw += (deltaX * sensitivity);

    if(pitch > 180.0f)
        pitch = -180.0f;
    else if(pitch < -180.0f)
        pitch = 180.0f;

    if(yaw > 180.0f)
        yaw = -180.0f;
    else if(yaw < -180.0f)
        yaw = 180.0f;

    frontDir.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    frontDir.y = sin(glm::radians(pitch));
    frontDir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}