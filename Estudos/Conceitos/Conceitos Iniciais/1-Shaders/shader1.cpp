#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "../includes/functions/mainFunc.cpp"

int main()
{
    GLFWwindow *window;

    if(!glfwInit())
    {
        show("GLFW nao pode ser inicialiazado");
        return -1;
    }

    window = glfwCreateWindow(680, 420, "Utilizando Shaders #01", NULL, NULL);
    if(!window)
    {
        show("Janela nao pode ser inicializada");
        glfwTerminate();
        return -1;
    }
    else{
        glfwMakeContextCurrent(window);
    }

    // GLEW
    GLenum error = glewInit();
    if(GLEW_OK != error)
    {
        show("GLEW nao pode ser inicializado");
        return -1;
    }

    show("Versao do OpenGL: " << glGetString(GL_VERSION));

    // Definições
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

    // Shader
    std::string src_vs = 
        "#version 450 core\n"
        "layout (location = 0) in vec2 position;\n"
        "void main(){\n"
        "gl_Position = vec4(position.x, position.y, 0.0f, 1.0);\n"
        "}"    
    ;

    std::string src_fs = 
        "#version 450 core\n"
        "out vec4 color;"
        "void main(){\n"
        "color = vec4(1.0f, 0.6f, 0.3f, 1.0f);\n"
        "}\n"
    ;

    const char *vertex_shader = &src_vs[0]; // Pode ser src_vs.c_str()
    const char *fragment_shader = src_fs.c_str();

    // Criando shader
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_shader, NULL);
    glCompileShader(vertex);

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_shader, NULL);
    glCompileShader(fragment);

    unsigned int shader = glCreateProgram();
    glAttachShader(shader, vertex);
    glAttachShader(shader, fragment);
    glLinkProgram(shader);

    glUseProgram(shader);
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    // Execução
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
 // std::stringstream