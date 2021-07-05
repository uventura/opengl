#include "Class/HeaderProgram.h"

int main()
{
    Application window("Light #03 - Light Casters", 640, 480, true);
    Menu imgui(window.getWindowPtr());

    glfwSetKeyCallback(window.getWindowPtr(), keyCamCallback);
    glfwSetScrollCallback(window.getWindowPtr(), scrollCamCallback);

    // Shader
    Shader obj("Files/Shaders/Shader21.shader");
    Shader light("Files/Shaders/Shader22.shader");

    // Object
    float vertices[] = 
    {
    // COORDS               NORMAL VECTORS     TEX COORDS
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    Buffer objBuffer(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    // Positions
    objBuffer.layout(3, 8 * sizeof(float), 0);
    // Normal Vectors
    objBuffer.layout(3, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // Texture Coordinates
    objBuffer.layout(2, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    Buffer lightBuffer(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    lightBuffer.layout(3, 8 * sizeof(float), 0);

    // Transformations
    glm::mat4 model(1.0f);
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Camera3D cam;
    frontDir = cam.getVecFront();

    glm::mat4 persp(1.0f);

    // Light
    float objColor[3] = {0.4f, 0.2f, 0.2f};
    float lightMove[3] = {0.0f, 0.385f, 3.333f};
    glm::vec3 lightPos(0.3f, 0.5f, 0.0f);

    float lightColor[3] = {1.0f, 1.0f, 1.0f};

    while(window.Execute())
    {
        window.Clear();
            
        imgui.newFrame();
            ImGui::Begin("Properties:");
                ImGui::SliderFloat3("Light Pos.", lightMove, -10.0f, 10.0f);
                ImGui::ColorEdit3("Light Color", lightColor);
                ImGui::ColorEdit3("Object Color", objColor);
            ImGui::End();
        imgui.render();

        lightPos.x = lightMove[0];
        lightPos.y = lightMove[1];
        lightPos.z = lightMove[2];

        if(!modeCursor)
        {
            glfwSetInputMode(window.getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(window.getWindowPtr(), cursorCamCallback);
        }
        else
        {
            glfwSetInputMode(window.getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPosCallback(window.getWindowPtr(), nullptr);
        }

        cam.setZoom(incrZoom);
        cam.setVecFront(frontDir);
        cam.moveCamera(keys);

        persp = glm::perspective(glm::radians(cam.getZoom()), (float)window.getWidth()/(float)window.getHeight(), 0.1f, 100.0f);

        glm::vec3 eyePos = cam.getCamPos();
        glm::vec3 frontPos = cam.getVecFront();

        obj.Use();
        obj.uniforfMat4fv("model", (float*)glm::value_ptr(model));
        obj.uniforfMat4fv("space", (float*)glm::value_ptr(persp * cam.getCamMatrix()));
        obj.uniform3fv("u_lightColor", lightColor[0], lightColor[1], lightColor[2]);
        obj.uniform3fv("u_objColor", objColor[0], objColor[1], objColor[2]);
        obj.uniform3fv("u_eyePos", eyePos.x, eyePos.y, eyePos.z);

        obj.uniform3fv("spot.position", eyePos.x, eyePos.y, eyePos.z);
        obj.uniform3fv("spot.direction", frontPos.x, frontPos.y, frontPos.z);
        obj.uniform1fv("spot.cutOff", glm::cos(glm::radians(12.5f)));
        obj.uniform1fv("spot.outerCutOff", glm::cos(glm::radians(25.5f)));

        objBuffer.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // LIGHT RENDER
        glm::mat4 modelLight(1.0f);
        modelLight = glm::translate(modelLight, lightPos);
        modelLight = glm::scale(modelLight, glm::vec3(0.5f, 0.5f, 0.5f));

        light.Use();
        light.uniforfMat4fv("trans", (float*)value_ptr(persp * cam.getCamMatrix() * modelLight));
        
        lightBuffer.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        window.Update();
    }
}