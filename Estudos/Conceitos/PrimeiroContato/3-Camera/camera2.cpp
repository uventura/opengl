#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "../includes/functions/mainFunc.cpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    GLFWwindow *window;

    if(!glfwInit())
    {
        show("Erro ao inicializar o GLFW.");
        return -1;
    }

    window = glfwCreateWindow(680, 420, "Aplicação de Transformações", NULL, NULL);
    if(!window)
    {
        show("Erro ao criar janela.");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    /* Pré definições sobre o GLFW e como a janela deve se comportar*/

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /*============================================================*/

    GLenum error = glewInit();
    if(GLEW_OK != error)
    {
        show("Erro ao inicializar o GLEW.");
    }

    show("Versao do GLEW: " << glewGetString(GLEW_VERSION));
    show("Versao do OpenGL: " << glGetString(GL_VERSION));
    show("Versao do GLFW: " << glfwGetVersionString());

    //<<<<<<<<<<| DEFINIÇÕES |>>>>>>>>>>
    float vertices[12] = 
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.8f, 0.0f,
        -0.5f,  0.8f, 0.0f
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
    shaderCode src = getShaderSource("../includes/shaders/camera2.shader");

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
    
        // Model Matrix (Matriz Global)
        glm::mat4 model(1.0f); // Matriz que descreve as rotações de espaço
        model = glm::rotate(model, glm::radians(-80.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        // View Matrix (Matriz de Visualização)
        glm::mat4 view(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, -0.1f, -1.0f));

        // View Form (Forma que será visualizado(ortograficamente ou com perspectiva))
        glm::mat4 perspective(1.0f);
        perspective = glm::perspective(glm::radians(45.0f), (float)(680 / 420), 0.1f, 300.0f);

    // Set Uniforms
    int u_model = glGetUniformLocation(shader1, "u_model");
    glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));

    int u_view = glGetUniformLocation(shader1, "u_view");
    glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view));

    int u_persp = glGetUniformLocation(shader1, "u_persp");
    glUniformMatrix4fv(u_persp, 1, GL_FALSE, glm::value_ptr(perspective));

    // Execução
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.1f, 1.0f);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader1);

    glfwTerminate();
    return 0;
}