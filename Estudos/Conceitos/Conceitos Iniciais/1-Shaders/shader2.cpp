#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "../includes/functions/mainFunc.cpp"

int main()
{
    GLFWwindow *window;

    if(!glfwInit())
    {
        show("Nao foi possivel inicializar a janela");
        return -1;
    }

    window = glfwCreateWindow(640, 480, "#02 Erros de Shader", NULL, NULL);

    if(!window)
    {
        show("Nao possivel criar a janela");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // GLEW
    GLenum error = glewInit();
    if(GLEW_OK != error)
    {
        show("Erro ao inicializar o GLEW");
        return -1;
    }
    else
    {
        show("Versao atual do OpenGL: " << glGetString(GL_VERSION));
    }

    // DEFINIÇÕES
    GLfloat points[6] =
    {
        0.0f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    std::string src_fs = 
    "#version 450 core\n"
    "out vec4 color"
    "void main(){\n"
    "color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n"
    ;

    const char* fs = src_fs.c_str();

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fs, NULL);
    glCompileShader(fragment);

    //<-----| Erros do Fragment Shader |----->

    //**** ESTA É A PARTE QUE ANALISA OS ERROS ****
    int sucesso, size;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &sucesso);//iv = integer value

    if(!sucesso)
    {
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &size);

        char info[size];
        glGetShaderInfoLog(fragment, sizeof(info), nullptr, info);

        show("Erro ao criar o shader: " << info);
    }
    // O CÓDIGO ACIMA FUNCIONA PARA VERTEX, BASTA TROCAR FRAGMENT POR VERTEX(A VAR. DO VERTEX SHADER)
    // Em &size pode ser colocado NULL ou nullptr caso não seja desejado.

    /* A diferença de nullptr para NULL, é que não importará o tipo que seja exigido, nullptr
    irá se adaptar àquele tipo, NULL é um tipo inteiro.*/

    unsigned int program = glCreateProgram();
    glAttachShader(program, fragment);
    glLinkProgram(program);

    //<----- LIDANDO COM ERROS DE LINKAGEM ----->
    glGetShaderiv(program, GL_LINK_STATUS, &sucesso);
    if(!sucesso)
    {
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &size);

        char info[size];
        glGetProgramInfoLog(program, sizeof(info), nullptr, info);

        show("Erro na linkagem: " << info << "[" << size << "]");
    }

    glUseProgram(program);
    glDeleteShader(fragment);

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