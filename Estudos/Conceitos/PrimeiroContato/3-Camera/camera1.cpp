#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "../includes/functions/mainFunc.cpp"

int main()
{
    GLFWwindow *window;
    if(!glfwInit())
    {
        show("Nao foi possivel inicializar GLFW.");
        return -1;
    }

    window = glfwCreateWindow(640, 480, "#01 - Space Transformations", NULL, NULL);
    if(!window)
    {
        show("A janela nao pode ser inicializada.");
        glfwTerminate();
    }
    
    glfwMakeContextCurrent(window);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLEW
    unsigned int error = glewInit();
    if(GLEW_OK != error)
    {
        show("Erro ao inicializar GLEW.\n");
        glfwTerminate();
    }

    show("Versao do OpenGL: " << glGetString(GL_VERSION));

    // Definições
    float vertices[12] = 
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    unsigned int indices[6] =
    {
        0, 1, 2,
        2, 3, 0
    };

    // Vertex Definitions
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // Element Buffer Object
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Shader
    shaderCode src = getShaderSource("../includes/shaders/camera1.shader");

     // Vertex Shader
     unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
     glShaderSource(vertex, 1, &src.vertexPtr, NULL);
     glCompileShader(vertex);

     // Vertex Shader Error Message
     int success, size;
     glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
     if(!success)
     {
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &size);

        char info[size];
        glGetShaderInfoLog(vertex, size, NULL, info);

        show("[VERTEX]\n" << info);
     }

     // Fragment Shader
     unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
     glShaderSource(fragment, 1, &src.fragmentPtr, NULL);
     glCompileShader(fragment);
     
     // Fragment Shader Error
     glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
     if(!success)
     {
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &size);

        char info[size];
        show("[FRAGMENT]\n" << info);
     }

    // Shader Program
    unsigned int shader1 = glCreateProgram();
    glAttachShader(shader1, vertex);
    glAttachShader(shader1, fragment);
    glLinkProgram(shader1);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glUseProgram(shader1);
    
    // Spacial Transformations in a Object
    glm::mat4 trans(1.0f);

    // Set Uniforms
    int u_trans = glGetUniformLocation(shader1, "transform");
    if(u_trans == -1)
        show("O uniform nao pode ser encontrado");

    // Execução
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
        
        if(glfwGetTime() >= 0.002)
        {
            trans = glm::rotate(trans, glm::radians(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            glfwSetTime(0);
        }

        glUniformMatrix4fv(u_trans, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader1);

    glfwTerminate();
}