#include "Class/HeaderProgram.h"

// Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

bool keys[1024];
bool firstMove = true;

// Manter a mesma velocidade de transição para todos
float deltaT = 0.0f;
float lastFrame = 0.0f;

// Movimentos do Mouse
float lastX = 320, lastY = 240; // Localizado no centro da tela
float pitch = 0.0f, yaw = 0.0f;

// Ângulo de Visão
float fov = 45.0f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    static int i = 0;

    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // Zoom

    if(fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset; // Aumenta o ângulo de visão quando y < 0 e diminui o angulo de visão quando y > 0

    if(fov <= 1.0f)
        fov = 1.0f;
    if(fov >= 45.0f)
        fov = 45.0f;
}

void do_movement()
{
    float cameraSpeed = 5.0f * deltaT; // deltaT para manter a velocidade da câmera constante.

    if(keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
        cameraPos += cameraFront * cameraSpeed;
    if(keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
        cameraPos -= cameraFront * cameraSpeed;
    if(keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if(keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMove)
    {
        // Para evitar que a primeira entrada do mouse não crie uma rotação estranha.
        lastX = xpos;
        lastY = ypos;
        firstMove = false;
    }

    // Delta Move
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Inverso pois a janela tem o sistema de coordenadas de baixo para cima.

    lastX = xpos; // Antiga posição vai ser igual a nova
    lastY = ypos;

    float sensitivity = 0.05f; // diminuir a velocidade do movimento.
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    pitch += yoffset; // O quanto movimenta para cima ou para baixo.
    yaw += xoffset;

    // Limitar a angulação de movimento em Pitch e Yaw
    if(pitch > 30.0f)
        pitch = 30.0f;
    if(pitch < -30.0f)
        pitch = -30.0f;

    // Determinar o vetor front(a direção para o qual a câmera aponta)
    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

int main()
{
    Application window("Camera #03", 640, 480, true);
    Menu imgui(window.getWindowPtr());

    glfwSetKeyCallback(window.getWindowPtr(), key_callback);
    glfwSetCursorPosCallback(window.getWindowPtr(), mouse_callback);
    glfwSetInputMode(window.getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetScrollCallback(window.getWindowPtr(), scroll_callback);

    // Shader
    Shader move("Files/Shaders/Shader06.shader");
    move.Use();

    // Cube
    float vertices[] = 
    {
        // Front
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
        // Back
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f
    };

    unsigned int indices[]=
    {
        // Front
        0, 1, 2,
        2, 3, 0,
        // Bottom
        0, 4, 5,
        0, 1, 5,
        // Right
        1, 2, 5,
        2, 5, 6,
        // Up
        2, 6, 7,
        2, 3, 7,
        // Left
        0, 3, 7,
        0, 4, 7,
        // Back
        4, 5, 7,
        5, 6, 7
    };

    Buffer vertex(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    vertex.layout(3, 3 * sizeof(float), 0);

    Buffer element(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));

    // Transformations
    float angle = glm::radians(228.0f);

    while(window.Execute())
    {
        window.Clear();

        deltaT = glfwGetTime() - lastFrame;
        lastFrame = glfwGetTime();

        lastFrame = glfwGetTime();

        imgui.newFrame();
        ImGui::Begin("Properties:");
            ImGui::SliderAngle("Angle", &angle, 0.0f, 360.0f);
        ImGui::End();
        imgui.render();

        glm::mat4 view(1.0f), model(1.0f), persp(1.0f);
        model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        persp = glm::perspective(glm::radians(fov), (float)window.getWidth()/(float)window.getHeight(), 0.1f, 100.0f);

        move.uniforfMat4fv("transform", (float*)glm::value_ptr(persp * view * model));

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        window.Update();
        do_movement();
    }
}