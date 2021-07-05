#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Class/shader.h"

int main()
{
    GLFWwindow *window;

    if(!glfwInit())
    {
        show("Erro ao inicializar GLFW");
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Uniforms e Estudos da linguagem GLSL", NULL, NULL);
    if(!window)
    {
        show("Erro ao criar janela");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // GLEW
    unsigned int info = glewInit();
    if(GLEW_OK != info)
    {
        show("Erro ao inicializar o glew");
        return -1;
    }
    show("Versao do OpenGL: " << glGetString(GL_VERSION));
    
    //[ Abaixo está listado a limitação de atributos de um vertex shader ]
    int maxShaderAttrib;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxShaderAttrib);
    show("Maximo de atributos de um vertex shader: " << maxShaderAttrib);

    //<<<<<| DEFINIÇÕES |>>>>>
    float vertices[6]
    {
         0.0f,  0.5f, 
        -0.5f, -0.5f,
         0.5f, -0.5f
    };
    //-> Vertex Buffer Object
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    //-> Shader
    shaderCode src = getShaderSource("../includes/shaders/shader3.shader");
    
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

    Shader shader = 

    double time = glfwGetTime(); // Função do OpenGL que obtém o tempo em segundos, desde a abertura do glfw.

    // Uniform
    int uniformColor = glGetUniformLocation(shader, "ourColor"); // Obter o Uniform
    glUniform4f(uniformColor, 0.3f, 0.2f, 0.8f, 1.0f); // Definir os valores do Uniform
    // Obs: A função getUniformLocation retorna -1 caso não encontre o uniform especificado.

    float colorAdd = 0.0f;
    bool go = true;

    //<<<<<| Execução |>>>>>
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        if(glfwGetTime() > 0.06f)
        {
            glUniform4f(uniformColor, 0.3f + colorAdd, 0.2f, 0.8f, 1.0f);

            if(colorAdd >= 1.0f)
                go = false;
            else if(colorAdd <= 0.0f)
                go = true;

            if(go)
                colorAdd += 0.1f;
            else
                colorAdd -= 0.1f;

            glfwSetTime(0); // Função que modifica o relógio do glfw.
        }

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    glDeleteProgram(shader);
}