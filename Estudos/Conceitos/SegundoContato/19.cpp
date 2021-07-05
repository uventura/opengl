#include "Class/HeaderProgram.h"

int main()
{
    Application window("Light #01 - Second Try", 640, 480, true);
    Menu imgui(window.getWindowPtr());

    glfwSetKeyCallback(window.getWindowPtr(), keyCamCallback);
    glfwSetScrollCallback(window.getWindowPtr(), scrollCamCallback);

    // Shader
    Shader obj("Files/Shaders/Shader17.shader");
    Shader light("Files/Shaders/Shader18.shader");

    // Object
    float vertices[] = 
    {
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

    unsigned int vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    // Normal Vectors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int lightBuffer;
    glGenBuffers(1, &lightBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, lightBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

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

    float ambient[3] = {0.25f, 0.20725f, 0.20725f};
    float diffuse[3] = {1.0f, 0.829f, 0.829f};
    float specular[3] = {0.296648f, 0.296648f, 0.296648f};
    float shine = 0.088f;

    float lightColor[3] = {1.0f, 1.0f, 1.0f};

    while(window.Execute())
    {
        window.Clear();
            
        imgui.newFrame();
            ImGui::Begin("Properties:");
                ImGui::SliderFloat3("Light Pos.", lightMove, -10.0f, 10.0f);
                ImGui::ColorEdit3("Ambient", ambient);
                ImGui::ColorEdit3("Diffuse", diffuse);
                ImGui::ColorEdit3("Specular", specular);
                ImGui::ColorEdit3("Shininess", &shine);
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

        obj.Use();
        obj.uniforfMat4fv("model", (float*)glm::value_ptr(model));
        obj.uniforfMat4fv("space", (float*)glm::value_ptr(persp * cam.getCamMatrix()));
        obj.uniform3fv("u_lightPos", lightPos.x, lightPos.y, lightPos.z);
        obj.uniform3fv("u_eyePos", eyePos.x, eyePos.y, eyePos.z);
        obj.uniform3fv("u_lightColor", lightColor[0], lightColor[1], lightColor[2]);
        obj.uniform3fv("u_objColor", objColor[0], objColor[1], objColor[2]);
        // Materials
        obj.uniform3fv("u_ambient", ambient[0], ambient[1], ambient[2]);
        obj.uniform3fv("u_diffuse", diffuse[0], diffuse[1], diffuse[2]);
        obj.uniform3fv("u_specular", specular[0], specular[1], specular[2]);
        obj.uniform1fv("u_shine", shine);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // LIGHT RENDER
        glm::mat4 modelLight(1.0f);
        modelLight = glm::translate(modelLight, lightPos);
        modelLight = glm::scale(modelLight, glm::vec3(0.5f, 0.5f, 0.5f));

        light.Use();
        light.uniforfMat4fv("trans", (float*)value_ptr(persp * cam.getCamMatrix() * modelLight));
        light.uniform3fv("u_lightColor", lightColor[0], lightColor[1], lightColor[2]);
        glBindBuffer(GL_ARRAY_BUFFER, lightBuffer);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        window.Update();
    }
}