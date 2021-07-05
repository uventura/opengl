#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "../include/shaderFile.cpp"

int main()
{
    GLFWwindow *window;

    if(!glfwInit())
    {
        show("Erro ao inicializar o GLFW");
        return -1;
    }

    window = glfwCreateWindow(680, 420, "Quadrado Dupla Cor", NULL, NULL);
    if(!window)
    {
        show("Erro ao criar janela");
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
        show("Erro ao inicializar o GLEW");
    }

    show("Versao do GLEW: " << glewGetString(GLEW_VERSION));
    show("Versao do OpenGL: " << glGetString(GL_VERSION));
    show("Versao do GLFW: " << glfwGetVersionString());

    //<=====| DEFINIÇÕES |=====>
    float vertices1[6] = 
    {
        // Triângulo 1
        -0.5f, 0.5f,
        -0.5f,-0.5f,
         0.5f,-0.5f
    };

    float vertices2[6] = 
    {
        // Triângulo 2
        0.5f,-0.5f,
         0.5f, 0.5f,
        -0.5f, 0.5f
    };

    // Primeiro Triângulo
    unsigned int vao1; // Vertex Array Object
    glGenVertexArrays(1, &vao1);
    glBindVertexArray(vao1);

    unsigned int vbo1; // Vertex Buffer Object
    glGenBuffers(1, &vbo1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glBindVertexArray(0);

    // Segundo Triângulo
    unsigned int vao2;
    glGenVertexArrays(1, &vao2);
    glBindVertexArray(vao2);
    
    unsigned int vbo2; // Vertex Buffer Object
    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glBindVertexArray(0);

    //<=====| SHADERS |=====>
    std::string src_fs1 = 
    "#version 450 core\n"
    "out vec4 color;\n"
    "void main(){\n"
    "color = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n"
    "}\n"
    ;

    std::string src_fs2 = 
    "#version 450 core\n"
    "out vec4 color;\n"
    "void main(){\n"
    "color = vec4(0.3f, 0.2f, 0.8f, 1.0f);\n"
    "}\n"
    ;

    // Primeiro Fragment Shader
    const char* frag1 = src_fs1.c_str();
    unsigned int fragment1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment1, 1, &frag1, NULL);
    glCompileShader(fragment1);

    unsigned int shader1 = glCreateProgram();
    glAttachShader(shader1, fragment1);
    glLinkProgram(shader1);
    glDeleteShader(fragment1);
    
    // Segundo Fragment Shader
    const char* frag2 = src_fs2.c_str();
    unsigned int fragment2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment2, 1, &frag2, NULL);
    glCompileShader(fragment2);

    unsigned int shader2 = glCreateProgram();
    glAttachShader(shader2, fragment2);
    glLinkProgram(shader2);
    glDeleteShader(fragment2);


    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader1);
        glBindVertexArray(vao2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shader2);
        glBindVertexArray(vao1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}