#include "Class/HeaderProgram.h"

int main()
{
    Application window("Camera #01", 640, 480, true);

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

    /* Camera
    Noções:
        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // Posição da câmera
        glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // um alvo ao qual a câmera aponta
        glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); // Vetor que descreve a direção da câmera
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // Um vetor que aponta para cima

        glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection)); // O vetor direita da câmera
        glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight); // o vetor para cima da câmera

        glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, up); // Matriz de visualização.
    */
    // Transformação
    glm::mat4 model(1.0f), persp(1.0f);
    model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    persp = glm::perspective(glm::radians(45.0f), (float)window.getWidth()/(float)window.getHeight(), 0.1f, 100.0f);

    // Criar Movimento
    float radius = 10.0f;
    float camx;
    float camz;

    while(window.Execute())
    {
        window.Clear();
        
        camx = sin(glfwGetTime()) * radius;
        camz = cos(glfwGetTime()) * radius;

        // Descreve a Câmera, passando os vetores do espaço global para o de visualização.
        glm::mat4 view(1.0f);
        view = glm::lookAt(glm::vec3(camx, 0.0f, camz), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        shade.uniforfMat4fv("transform", (float*)glm::value_ptr(persp * view * model));
        glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);

        window.Update();
    }
}