// Light Concepts

#include "Class/HeaderProgram.h"

int main()
{
    Application window("Light #01", 640, 480, true);

    // Shader
    Shader objShader("Files/Shaders/Shader07.shader");
    Shader lightShader("Files/Shaders/Shader08.shader");

    // Objects
    float vertices[] = 
    {
        // Front
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
        // Back
        -0.5f, -0.5f, -0.8f,
         0.5f, -0.5f, -0.8f,
         0.5f,  0.5f, -0.8f,
        -0.5f,  0.5f, -0.8f
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

    // Object
    unsigned int vaoObj, vaoLight;
    glGenVertexArrays(1, &vaoObj);
    glGenVertexArrays(1, &vaoLight);

    glBindVertexArray(vaoObj);

    Buffer obj(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    obj.layout(3, 6 * sizeof(float), 0);
    obj.layout(3, 6 * sizeof(float), (void*)(&vertices[3]));

    Buffer elObj(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));

    // Light
    glBindVertexArray(vaoLight);

    Buffer light(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    light.layout(3, 6 * sizeof(float), 0);

    Buffer elLight(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));

    glBindVertexArray(0);

    // Transformations

    // Object
    glm::mat4 model1(1.0f);
    model1 = glm::rotate(model1, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model1 = glm::scale(model1, glm::vec3(0.5f, 0.5f, 0.5f));
    model1 = glm::translate(model1, glm::vec3(-0.8f, 0.0f, 0.0f));

    // Light
    glm::vec3 lightPosition(3.0f, 0.3f, -0.5f);

    glm::mat4 model2(1.0f);
    model2 = glm::rotate(model2, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 1.0f));
    model2 = glm::scale(model2, glm::vec3(0.2f, 0.2f, 0.2f));
    model2 = glm::translate(model2, glm::vec3(3.0f, 0.3, -0.5f));

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    while(window.Execute())
    {
        window.Clear();

        glm::mat4 persp(1.0f);
        persp = glm::perspective(glm::radians(45.0f), (float)window.getWidth()/(float)window.getHeight(), 0.1f, 100.0f);

        glBindVertexArray(vaoObj);
        objShader.Use();
        objShader.uniforfMat4fv("transform", (float*)glm::value_ptr(persp * view * model1));
        objShader.uniform3fv("objColor", 1.0f, 0.4f, 1.0f);
        objShader.uniform3fv("lightColor", 1.0f, 1.0f, 1.0f);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glBindVertexArray(vaoLight);
        lightShader.Use();
        lightShader.uniforfMat4fv("transform", (float*)glm::value_ptr(persp * view * model2));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        window.Update();
    }
}