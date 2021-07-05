// Shader3: Verificar o funcionamento da função para obter o shader.

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Class/shader.h"

int main()
{
    GLFWwindow *window;

    if(!glfwInit())
    {
        show("Erro ao inicializar o GLFW.");
        return -1;
    }

    window = glfwCreateWindow(680, 420, "Verificando o Funcionamento do GSL", NULL, NULL);
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

    // Vertex Buffer Object
    float vertices[6] = 
    {
         0.5f, -0.5f,
         0.0f,  0.5f,
        -0.5f, -0.5f
    };

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    // Shader
    /*
    shaderCode shaderSrc = getShaderSource("../includes/shaders/shader1.shader");

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &shaderSrc.fragmentPtr, NULL);
    glCompileShader(fragment);

    int compile;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &compile);
    if(!compile)
    {
        int size;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &size);

        char info[size];
        glGetShaderInfoLog(fragment, size, 0, info);

        show(info);
    }

    unsigned int shader = glCreateProgram();
    glAttachShader(shader, fragment);
    glLinkProgram(shader);

    glDeleteShader(fragment);
    glUseProgram(shader);*/

    Shader shader("../includes/shaders/shader1.shader");
    shader.Use();

    //<<<<<<<<<<| EXECUÇÃO |>>>>>>>>>>
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}