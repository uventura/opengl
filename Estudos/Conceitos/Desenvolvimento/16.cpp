#include "Class/HeaderProgram.h"

int main()
{
    Application window("Light #03", 640, 480, true);
    Menu imgui(window.getWindowPtr());

    glfwSetKeyCallback(window.getWindowPtr(), keyCamCallback);
    glfwSetScrollCallback(window.getWindowPtr(), scrollCamCallback);

    // Camera
    Camera3D cam;
    frontDir = cam.getVecFront();

    // Shaders
    Shader cubeShader("Files/Shaders/Shader14.shader");
    Shader lightShader("Files/Shaders/Shader13.shader");
    Shader planeShader("Files/Shaders/Shader12.shader");

    // Object
    float cube[] = 
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

    float plane[] = 
    {
        -0.8f, -0.8f, 0.0f,
         0.8f, -0.8f, 0.0f,
         0.8f,  0.8f, 0.0f,

         0.8f,  0.8f, 0.0f,
        -0.8f,  0.8f, 0.0f,
        -0.8f, -0.8f, 0.0f
    };

    Buffer cubeBuff(GL_ARRAY_BUFFER, cube, sizeof(cube));
    cubeBuff.layout(3, 6 * sizeof(float), 0);
    cubeBuff.layout(3, 6 * sizeof(float), (void*)(&cube[3]));

    Buffer lightBuff(GL_ARRAY_BUFFER, cube, sizeof(cube));
    lightBuff.layout(3, 6 * sizeof(float), 0);

    Buffer planeBuff(GL_ARRAY_BUFFER, plane, sizeof(plane));
    planeBuff.layout(3, 3 * sizeof(float), 0);

    // Transformation
    glm::mat4 model1(1.0f);
    model1 = glm::rotate(model1, glm::radians(40.0f), glm::vec3(0.5f, -1.0f, 0.0f));

    glm::mat4 model2(1.0f);
    model2 = glm::translate(model2, glm::vec3(0.0f, -1.6f, 0.0f));
    model2 = glm::rotate(model2, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model2 = glm::scale(model2, glm::vec3(5.0f, 5.0f, 5.0f));

    // Caracteristics
    float lightMove[3] = {2.0f, 2.0f, 0.0f};
    glm::vec3 lightPos(2.0f, 2.0f, 0.0f);

    float LI = 0.1f;
    float rX = 2.0f, rZ = 0.0f;
    float angle = 0.0f;
    float lastTime = glfwGetTime();

    // Execução
    while(window.Execute())
    {
        window.Clear();

        if(glfwGetTime() - lastTime > 0.01f)
        {
            ++angle;
            lastTime = glfwGetTime();
        }

        rX = 2 * sin(glm::radians(angle));
        rZ = 3 * cos(glm::radians(angle));

        // Menu
        imgui.newFrame();
            ImGui::Begin("Properties:");
                ImGui::SliderFloat3("Light Pos.", lightMove, -10.0f, 10.0f);
                ImGui::SliderFloat("Light Intes.", &LI, -1.0f, 1.0f);
            ImGui::End();
        imgui.render();

        lightMove[0] = rX;
        lightMove[2] = rZ;
        lightPos = glm::vec3(lightMove[0], lightMove[1], lightMove[2]);

        glm::mat4 model3(1.0f);
        model3 = glm::translate(model3, lightPos);
        model3 = glm::scale(model3, glm::vec3(0.5f, 0.5f, 0.5f));

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
        glm::vec3 camPos = cam.getCamPos();

        glm::mat4 persp(1.0f);
        persp = glm::perspective(glm::radians(cam.getZoom()), (float)window.getWidth()/(float)window.getHeight(), 0.1f, 100.0f);

        cubeBuff.bind();
        cubeShader.Use();
        cubeShader.uniforfMat4fv("model", (float*)glm::value_ptr(model1));
        cubeShader.uniforfMat4fv("global", (float*)glm::value_ptr(persp * cam.getCamMatrix()));
        cubeShader.uniform3fv("lightColor", 1.0f, 1.0f, 1.0f);
        cubeShader.uniform3fv("objColor", 0.4f, 0.2f, 0.2f);
        cubeShader.uniform3fv("lightPos", lightMove[0], lightMove[1], lightMove[2]);
        cubeShader.uniform3fv("viewPos", camPos.x, camPos.y, camPos.z);
        cubeShader.uniform1fv("lightIntens", LI);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        cubeBuff.unbind();

        lightBuff.bind();
        lightShader.Use();
        lightShader.uniforfMat4fv("trans", (float*)glm::value_ptr(persp * cam.getCamMatrix() * model3));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        lightBuff.unbind();

        planeBuff.bind();
        planeShader.Use();
        planeShader.uniforfMat4fv("trans", (float*)glm::value_ptr(persp * cam.getCamMatrix() * model2));
        glDrawArrays(GL_TRIANGLES, 0, 6);

        window.Update();
    }
}