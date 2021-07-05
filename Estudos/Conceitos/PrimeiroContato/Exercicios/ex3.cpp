#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "../includes/functions/mainFunc.cpp"

int main()
{
    GLFWwindow *window;

    if(!glfwInit())
    {
        show("Erro ao inicializar o GLFW.");
        return -1;
    }

    window = glfwCreateWindow(680, 420, "Fragment Interpolation", NULL, NULL);
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

    show("Versao do GLEW: " << glewGetString(GLEW_VERSION));
    show("Versao do OpenGL: " << glGetString(GL_VERSION));
    show("Versao do GLFW: " << glfwGetVersionString());

    //<<<<<<<<<<| DEFINIÇÕES |>>>>>>>>>>
    float vertices[15]
    {
         0.0f,  0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f
    };
    //-> Vertex Buffer Object
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position Attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    // Colors Vertexes
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*) 8);

    //-> Shader
    shaderCode src = getShaderSource("../includes/shaders/shader4.shader");
    
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &src.vertexPtr, NULL);
    glCompileShader(vertex);
    
    int status;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);
    if(!status)
    {
        int size;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &size);

        char info[size];
        glGetShaderInfoLog(vertex, size, NULL, info);

        show(info);
    }

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &src.fragmentPtr, NULL);
    glCompileShader(fragment);

    // Shader Program
    unsigned int shader = glCreateProgram();
    glAttachShader(shader, vertex);
    glAttachShader(shader, fragment);
    glLinkProgram(shader);

    glUseProgram(shader);
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    //<<<<<| Execução |>>>>>
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    glDeleteProgram(shader);
    return 0;
}