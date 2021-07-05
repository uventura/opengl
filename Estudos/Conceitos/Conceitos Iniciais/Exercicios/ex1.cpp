// FORMAR UM QUADRADO NÃO UTILIZANDO UM VERTEX ARRAY

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "../include/shaderFile.cpp"

int main(void)
{
    // GLFW

    GLFWwindow *window;

    if(!glfwInit())
    {
        show("Nao foi possivel inicializar o GLFW");
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Quadrado", NULL, NULL);
    if(!window)
    {
        show("Nao foi possivel criar a janela");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    // GLEW
    unsigned int error = glewInit();
    if(GLEW_OK != error)
    {
        show("Erro ao inicializar o GLEW");
        return -1;
    }
    else
    {
        show("Versao do OpenGL" << glGetString(GL_VERSION));
    }

    // DEFINIÇÕES  
    float vertices[12] = 
    {
        // Triangulo 1
        -0.5f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f,
        // Triangulo 2
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f
    };

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    // SHADER
    std::string src_fs = 
    "#version 450 core\n"
    "out vec4 color;\n"
    "void main(){\n"
    "color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n"
    ;

    const char *fs = src_fs.c_str();
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fs, NULL);
    glCompileShader(fragment);

    int sucesso;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &sucesso);

    if(!sucesso)
    {
        int size;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &size);

        char info[size];
        glGetShaderInfoLog(fragment, size, nullptr, info);

        show("Erro ao compilar o Fragment -> " << info);
    }

    unsigned int shader = glCreateProgram();
    glAttachShader(shader, fragment);
    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &sucesso);
    if(!sucesso)
    {
        int size;
        glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &size);

        char info[size];
        glGetProgramInfoLog(shader, size, NULL, info);

        show("Erro na linkagem -> " << info);
    }

    glUseProgram(shader);
    glDeleteShader(fragment);

    // EXECUÇÃO
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

/*
NOTAS:
    É possível colocar vários dados dentro de um vertex buffer, porque o único fator a ser
considerado é como os vertices estão estruturados em sua memória, a quantidade dos mesmos
não importa para casos como esses.
*/