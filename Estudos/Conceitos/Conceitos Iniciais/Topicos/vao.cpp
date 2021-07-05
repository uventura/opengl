// <<<<<<<<<< Vertex Array Object >>>>>>>>>>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "../includes/functions/mainFunc.cpp"

int main()
{
    GLFWwindow *window;

    if(!glfwInit())
    {
        show("Glfw nao inicializou");
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Vertex Array Object", NULL, NULL);
    if(!window)
    {
        show("Janela nao pode ser criada");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    unsigned int status = glewInit();
    if(GLEW_OK != status)
    {
        show("Erro ao inicializa o glew");
        return -1;
    }

    // VERTEX ARRAY OBJECT

    /* A função de um vertex array object é salvar o estado de
    um vertex buffer object, salvar suas configurações já descritas
    , o vertex array object facilita o momento em que deseja-se 
    habilitar o uso e desuso de um objeto.*/

    unsigned int vao; // Define a variável de endereço do vertex array
    glGenVertexArrays(1, &vao); // Cria um vertex array
    glBindVertexArray(vao); // Habilita o uso do vertex array criado

    //<-----| Criando um Objeto |----->
    float vertices[6] = 
    {
        0.0f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f
    };

    unsigned int vbo;// Vertex Buffer Object
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glBindVertexArray(0); // Desabilita o uso do Vertex Array ativado

    //<----- Shader ----->
    std::string src_fs = 
    "#version 450 core\n"
    "out vec4 color;\n"
    "void main(){\n"
    "color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n"
    ;

    // Fragment Shader
    const char *fragment = &src_fs[0];
    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment, NULL);
    glCompileShader(fs);
    
    int tudocerto;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &tudocerto);
    if(!tudocerto)
    {
        int size;
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &size);

        char info[size];
        glGetShaderInfoLog(fs, size, NULL, info);

        show("Fragment Shader Error -> " << info);
    }

    // Shader Program
    unsigned int shader = glCreateProgram();
    glAttachShader(shader, fs);
    glLinkProgram(shader); // Relaciona as partes de attach com o que irá fazer

    glGetProgramiv(shader, GL_LINK_STATUS, &tudocerto);
    if(!tudocerto)
    {
        int size;
        glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &size);

        char info[size];
        glGetProgramInfoLog(shader, size, NULL, info);

        show("Erro em link program -> " << info);
    }

    glUseProgram(shader);
    glDeleteShader(fs);

    glBindVertexArray(vao); // Reutilizando um vertex array já criado.

    // Execução
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}