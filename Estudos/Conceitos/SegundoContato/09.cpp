#include "Class/HeaderProgram.h"

int main()
{
    Application window("Hello World!", 640, 480, true);
    Menu imgui(window.getWindowPtr());

    Shader shade("Files/Shaders/Shader04.shader");
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

    // Transformations
    glm::mat4 persp(1.0f);
    persp = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

    float angle = glm::radians(-55.0f);

    while(window.Execute())
    {
        window.Clear();

        imgui.newFrame();
            ImGui::Begin("Object Properties:");
                ImGui::ColorEdit3("Color", rgb);
                ImGui::SliderAngle("Rotacionar", &angle, -360.0f, 1800.0f);
            ImGui::End();
        imgui.render();

        glm::mat4 model(1.0f), view(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.3f));
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.3f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        shade.uniforfMat4fv("transform", (float*)glm::value_ptr(persp * view * model));
        shade.uniform4fv("u_color", rgb[0], rgb[1], rgb[2], 1.0f);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.Update();
    }
}