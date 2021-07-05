#include "Class/HeaderProgram.h"

int main()
{
    Application window("Light #02", 640, 480, true);
    Menu imgui(window.getWindowPtr());

    // Shaders
    Shader obj("Files/Shaders/Shader09.shader");
    Shader light("Files/Shaders/Shader10.shader");

    // Object
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    unsigned int vObj, vLight;

    glGenVertexArrays(1, &vObj);
    glGenVertexArrays(1, &vLight);

    glBindVertexArray(vObj);
    Buffer vertexBuff(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    vertexBuff.layout(3, 6 * sizeof(float), 0);
    vertexBuff.layout(3, 6 * sizeof(float), (void*)(&vertices[3]));

    glBindVertexArray(vLight);
    Buffer lightBuff(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    lightBuff.layout(3, 6 * sizeof(float), 0);
    glBindVertexArray(0);

    // Transformations

    //-> Obj:
    glm::mat4 model1(1.0f), view(1.0f), persp(1.0f);
    model1 = glm::rotate(model1, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    model1 = glm::translate(model1, glm::vec3(-0.7f, 0.0f, 0.0f));
    //model1 = glm::scale(model1, glm::vec3(0.5f, 0.5f, 0.5f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));

    //-> Light:
    glm::vec3 lightPos(1.0f, 0.8f, 2.0f);
    glm::vec3 eyePos(0.0f, 0.0f, -5.0f);

    while(window.Execute())
    {
        window.Clear();

        imgui.newFrame();
        ImGui::SliderFloat("Light Px: ", &lightPos.x, -3.0f, 3.0f);
        ImGui::SliderFloat("Light Py: ", &lightPos.y, -3.0f, 3.0f);
        ImGui::SliderFloat("Light Pz: ", &lightPos.z, -3.0f, 3.0f);
        imgui.render();

        glm::mat4 model2(1.0f);
        model2 = glm::rotate(model2, glm::radians(45.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        model2 = glm::translate(model2, lightPos);
        model2 = glm::scale(model2, glm::vec3(0.3f, 0.3f, 0.3f));

        persp = glm::perspective(glm::radians(45.0f), (float)window.getWidth()/(float)window.getHeight(), 0.1f, 100.0f);
        
        glBindVertexArray(vObj);
        obj.Use();
        obj.uniforfMat4fv("model", (float*)glm::value_ptr(model1));
        obj.uniforfMat4fv("space", (float*)glm::value_ptr(persp * view));
        obj.uniform3fv("lightColor", 1.0f, 1.0f, 1.0f);
        obj.uniform3fv("objColor", 1.0f, 0.5f, 0.31f);
        obj.uniform3fv("lightPos", lightPos.x, lightPos.y, lightPos.z);
        obj.uniform3fv("eyePos", eyePos.x, eyePos.y, eyePos.z);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(vLight);
        light.Use();
        light.uniforfMat4fv("transform", (float*)glm::value_ptr(persp * view * model2));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        window.Update();
    }
}