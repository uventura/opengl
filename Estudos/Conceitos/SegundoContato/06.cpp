#include "Class/HeaderProgram.h"

int main()
{
    Application window("Transformações", 640, 480, true);

    // Shader
    Shader shader("Files/Shaders/Shader03.shader");
    shader.Use();

    // Buffers
    float vertices[] = 
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f 
    };

    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };

    Buffer square(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    square.layout(3, 3 * sizeof(float), 0);

    Buffer element(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));

    // Transformations
    float propor, back;
    float i, j, ix, iy;

    // Execution
    while(window.Execute())
    {
        window.Clear();

        propor = (float)window.getWidht() / (float)window.getHeight();
        back = 1.0f;

        glm::mat4 resize(1.0f), trans(1.0f);
        trans = glm::translate(trans, glm::vec3(-back + 0.10f, -back + (0.10f * propor), 0.0f));
        resize = glm::scale(resize, glm::vec3(0.15f, 0.15f * propor, 1.0f));
        shader.uniforfMat4fv("transform", (float*)glm::value_ptr(trans * resize));
        
        ix = 0.0f;
        iy = 0.0f;
        for(i = 0; i < 8; ++i)
        {
            for(j = 0; j < 6; ++j)
            {
                shader.uniform4fv("move", ix, iy, 0.0f, 0.0f);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                iy += 1.23f;
            }
            ix += 1.23f;
            iy = 0.0f;
        }

        window.Update();
    }
}