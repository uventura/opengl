#include "Class/HeaderProgram.h"

// Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // Vetor posição
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // Vetor direção
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); // Vetor que aponta para cima

// Uso de Teclados
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    float cameraSpeed = 0.05f;
    if(key == GLFW_KEY_W)
        cameraPos += cameraSpeed * cameraFront;
    if(key == GLFW_KEY_S)
        cameraPos -= cameraSpeed * cameraFront;
    if(key == GLFW_KEY_A)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if(key == GLFW_KEY_D)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

int main()
{
    Application window("Camera #01", 640, 480, true);
    Menu imgui(window.getWindowPtr());

    glfwSetKeyCallback(window.getWindowPtr(), key_callback);

    // Shader
    Shader shade("Files/Shaders/Shader05.shader");
    shade.Use();

    // Object
    float rgb[3] = {1.0f, 0.4f, 0.3f};

    float vertices[] = 
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[]=
    {
        0, 1, 2,
        2, 3, 0
    };

    Buffer vbuffer(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    vbuffer.layout(2, 2 * sizeof(float), 0);

    Buffer ebuffer(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));

    // Transformação
    glm::mat4 model(1.0f), persp(1.0f);
    persp = glm::perspective(glm::radians(45.0f), (float)window.getWidth()/(float)window.getHeight(), 0.1f, 100.0f);

    float angulo = glm::radians(-10.0f);

    while(window.Execute())
    {
        window.Clear();
        
        imgui.newFrame();
        ImGui::Begin("Object Properties:");
            ImGui::SliderAngle("Angle", &angulo, 0, 360);
        ImGui::End();
        imgui.render();

        glm::mat4 view(1.0f), model(1.0f);
        model = glm::rotate(model, angulo, glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        shade.uniforfMat4fv("transform", (float*)glm::value_ptr(persp * view * model));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.Update();
    }
}