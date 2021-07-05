#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "../includes/functions/mainFunc.cpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../includes/libs/stb_image/stb_image.h"

int main()
{
    GLFWwindow *window;

    if(!glfwInit())
    {
        show("Erro ao inicializar o GLFW.");
        return -1;
    }

    window = glfwCreateWindow(640, 480, "#01 - Utilizando Texturas", NULL, NULL);
    if(!window)
    {
        show("Erro ao criar janela.");
        glfwTerminate();
        return -1;
    }

    /* Pré definições sobre o GLFW e como a janela deve se comportar*/

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

    glViewport(0, 0, 640, 480);
    //<<<<<<<<<<| DEFINIÇÕES |>>>>>>>>>>

    // Objeto
    float vertices[16] = 
    {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };

    unsigned int indices[6] = 
    {
        0, 1, 3,
        1, 2, 3
    };
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    unsigned int vao; // Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo; // Vertex Buffer Object
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int ebo; // Element Buffer Object
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Layout 0
    glEnableVertexAttribArray(0); // Definições de Posição do Objeto
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    // Layout 1
    glEnableVertexAttribArray(1); // Definições da Posição da Textura
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*) 4);

    glBindVertexArray(0);
    // Shader
    shaderCode src = getShaderSource("../includes/shaders/shader5.shader");

    /* Vertex Shader*/
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &src.vertexPtr, NULL);
    glCompileShader(vertex);

    int statusToCompile;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &statusToCompile);
    if(!statusToCompile)
    {
        int size;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &size);

        char info[size];
        glGetShaderInfoLog(vertex, size, NULL, info);

        show("[VERTEX]\n"<< info);
    }

    /* Fragment Shader*/
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &src.fragmentPtr, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &statusToCompile);
    if(!statusToCompile)
    {
        int size;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &size);

        char info[size];
        glGetShaderInfoLog(fragment, size, NULL, info);

        show("[FRAGMENT]\n" << info);
    }
    
    /* Program */
    unsigned int shader = glCreateProgram();
    glAttachShader(shader, vertex);
    glAttachShader(shader, fragment);
    glLinkProgram(shader);
    
    glUseProgram(shader);
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    // Textura
    ImageBMP img = LoadBMP("../includes/images/passaro.bmp");

    unsigned int texture; // Definindo a variável de endereçamento da textura
    glGenTextures(1, &texture); // Criando a textura
    glBindTexture(GL_TEXTURE_2D, texture); // Selecionando a Textura

    // Associando uma imagem a um Textura Criada
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, img.width, img.height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data);

    // Parâmetros sobre a Textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0); // Deselecionando a Textura

    delete(img.data);

    int u_tex = glGetUniformLocation(shader, "u_tex");
    if(u_tex == -1)
        show("Uniform nao encontrado");
    else
        glUniform1i(u_tex, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);        

    //<<<<<<<<<<| EXECUÇÃO |>>>>>>>>>>
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindTexture(GL_TEXTURE_2D, texture);  

        glUseProgram(shader);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    glDeleteProgram(shader);
    glDeleteTextures(1, &texture);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    return 0;
}