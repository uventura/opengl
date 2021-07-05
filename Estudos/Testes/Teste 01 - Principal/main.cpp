#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Class/Shader.h"

#include <iostream>
#define show(msg) std::cout << msg << std::endl

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "libs/imgui/imgui.h"
#include "libs/imgui/examples/imgui_impl_glfw.h"
#include "libs/imgui/examples/imgui_impl_opengl3.h"

int main()
{
    GLFWwindow *window;

    if(!glfwInit())
    {
        show("Erro ao inicializar o GLFW.");
        return -1;
    }

    window = glfwCreateWindow(680, 420, "Project Window", NULL, NULL);
    if(!window)
    {
        show("Erro ao criar janela.");
        glfwTerminate();
        return -1;
    }

    /* Pré definições sobre o GLFW e como a janela deve se comportar*/

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /*============================================================*/

    glfwMakeContextCurrent(window);

    GLenum error = glewInit();
    if(GLEW_OK != error)
    {
        show("Erro ao inicializar o GLEW.");
    }

    show("==========================================");
    show("Versao do GLEW: " << glewGetString(GLEW_VERSION));
    show("Versao do OpenGL: " << glGetString(GL_VERSION));
    show("Versao do GLFW: " << glfwGetVersionString());
    show("==========================================");

    //<<<<<<<<<<| DEFINIÇÕES |>>>>>>>>>>
    float vertices[36 * 3] =
    {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    unsigned int indices[6] = 
    {
        0, 1, 2,
        0, 2, 3
    }; 

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
/*
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
*/
    //<<<<<<<<<<<| IMGUI |>>>>>>>>>>
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 150");
        
        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

    ImVec4 color = ImVec4(0.6f, 0.5f, 0.1f, 1.0f);

    // SHADER
        Shader shader1("Shaders/shader1.shader");
        shader1.Use();
        shader1.SetUniformf("u_color", 4, (const float *)&color);

    // Transformations
        float position[3] = {0.0f, 0.0f, 0.0f};
        float prevPosition[3] = {0.0f, 0.0f, 0.0f};

        glm::mat4 model(1.0f);
        glm::mat4 view(1.0f);
        glm::mat4 world(1.0f);
        
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::translate(view,  glm::vec3(0.0f, 0.0f, -3.0f));
        world = glm::perspective(glm::radians(45.0f), (float)width/height, 0.1f, 100.0f);

        shader1.SetUniformMatrix4fv("transform", glm::value_ptr(world * view * model));

    // Imgui Parameters
        float angleX = 0.0f, pAngleX = angleX;
        float angleY = 0.0f, pAngleY = angleY;
        float angleZ = 0.0f, pAngleZ = angleZ;

        float anglePersp = 45.0f, pAnglePersp = anglePersp;
        float approximation = -3.0f;
        float distance = 0.0f, pDistance = distance;

    //<<<<<<<<<<| EXECUÇÃO |>>>>>>>>>>
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // render your GUI
        ImGui::Begin("Object Properties");
            ImGui::ColorEdit4("Color: ", (float *)&color);
            ImGui::SliderFloat3("Position: ", position, 0.0f, 1.0f);
            ImGui::SliderFloat("Angle X", &angleX, 0.0f, 360.0f);
            ImGui::SliderFloat("Angle Y", &angleY, 0.0f, 360.0f);
            ImGui::SliderFloat("Angle Z", &angleZ, 0.0f, 360.0f);
            ImGui::SliderFloat("Angle Perspective", &anglePersp, 0.0f, 180.0f);
            ImGui::SliderFloat("Distance View", &distance, 0.1f, 2.0f);
        ImGui::End();
        
        if(pAngleX != angleX)
            model = glm::rotate(model, glm::radians(-(angleX - pAngleX)), glm::vec3(1.0f, 0.0f, 0.0f));
        if(pAngleY != angleY)
            model = glm::rotate(model, glm::radians(-(angleY - pAngleY)), glm::vec3(0.0f, 1.0f, 0.0f));
        if(pAngleZ != angleZ)
            model = glm::rotate(model, glm::radians(-(angleZ - pAngleZ)), glm::vec3(0.0f, 0.0f, 1.0f));    
        if(pAnglePersp != anglePersp)
            world = glm::perspective(glm::radians(anglePersp), (float)width/height, 0.1f, 300.0f);

        view = glm::translate(view,  glm::vec3(0.0f, 0.0f, (distance - pDistance)));

        shader1.SetUniformf("u_color", 4, (const float *)&color);

        // View
        shader1.SetUniformMatrix4fv("transform", glm::value_ptr(world * view * model));

        // Render Figure
        glPointSize(10.0f);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        pAngleX = angleX;
        pAngleY = angleY;
        pAngleZ = angleZ;
        pAnglePersp = anglePersp;
        pDistance = distance;

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}