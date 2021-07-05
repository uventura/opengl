#include "Class/Application.h"
#include "Class/Buffer.h"
#include "Class/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    Application window("Olá Novo Mundo!", 640, 480, true);

    float vertices[]=
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };

    // Shader
    Shader shader("Files/Shaders/Shader01.shader");
    shader.Use();

    // Object Data
    Buffer vbo(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    vbo.layout(2, 2 * sizeof(float), 0);

    Buffer ebo(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));

    // Execution
    while(window.Execute())
    {
        window.Clear();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        shader.uniform4fv("ourColor", 0.8f, 0.1f, 0.2f, 1.0f);

        window.Update();
    }
}