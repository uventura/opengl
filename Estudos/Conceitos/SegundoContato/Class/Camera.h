#pragma once
#include "MainHeader.h"

class Camera3D
{
protected:
    glm::vec3 m_cameraPos, m_cameraFront, m_cameraUp;
    float m_cameraZoom, m_cameraSpeed;

public:
    Camera3D();

    inline void setCamPos(glm::vec3 camPos){m_cameraPos = camPos;};
    inline void setVecFront(glm::vec3 camFrontPos){m_cameraFront = glm::normalize(camFrontPos);};
    void setZoom(float zoom);

    inline glm::vec3 getCamPos(){return m_cameraPos;};
    inline glm::vec3 getVecFront(){return m_cameraFront;}
    inline glm::vec3 getVecUp(){return m_cameraUp;};
    inline float getZoom(){return m_cameraZoom;};

    inline glm::mat4 getCamMatrix(){return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);};

    void moveCamera(bool* cam_keys);
};
/*
class Camera2D: public Camera3D
{
    void moveCamera(bool* cam_keys)
    {
        if(cam_keys[GLFW_KEY_W] || cam_keys[GLFW_KEY_UP])
            m_cameraPos += m_cameraUp * m_cameraSpeed;
        if(cam_keys[GLFW_KEY_S] || cam_keys[GLFW_KEY_DOWN])
            m_cameraPos -= m_cameraUp * m_cameraSpeed;
        if(cam_keys[GLFW_KEY_A] || cam_keys[GLFW_KEY_LEFT])
            m_cameraPos += glm::normalize(glm::cross(m_cameraUp, m_cameraFront)) * m_cameraSpeed;
        if(cam_keys[GLFW_KEY_D] || cam_keys[GLFW_KEY_RIGHT])
            m_cameraPos -= glm::normalize(glm::cross(m_cameraUp, m_cameraFront)) * m_cameraSpeed;
    };
};*/