// Element Buffer Object

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#define show(msg) std::cout << msg << std::endl;

int main()
{
    GLFWwindow *window;

    if(!glfwInit()) return -1;
    window = glfwCreateWindow(640, 480, "Element Buffer Object", NULL, NULL);

    if(!window)
    {
        glfwTerminate();
        show("Erro ao criar a janela");
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
    
    // DEFINIÇÕES
    float vertices[12] = 
    {
        // Triangulo 1
        -0.5f, 0.5f,   // Vertice de Indice 0
        -0.5f,-0.5f,   // Vertice de Indice 1
         0.5f,-0.5f,   // Vertice de Indice 2
         0.5f, 0.5f    // Vertice de Indice 3
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Element Buffer Object
    /* 
        No exercício número 1, um quadrado foi renderizado utilizando um buffer de
    vertices relativamente grande para que fosse formado um quadrado, já que o mesmo
    era a composição de dois triângulos. Para que isso pudesse ser feito o que teve
    de ser feito é descrever as coordenadas de cada um dos mesmos, uma maneira de
    simplificar esse processo é através de um Element Buffer Object, basicamente
    ele utiliza os indices de cada um dos vertices para que seja formado um triângulo
    , basta que seja informado a ordem dos indices que o OpenGL saberá quais retas
    devem ser formadas e entre quais vertices.
        A principal consequência do uso de elements buffers é a redução de memória.
    Definção principal:

        Element Buffer Objetct : descrevem como vertices irão se relacionar para que um
    objeto seja formado, retas, triângulos, quadrados e qualquer outra figura 3D.
    */

    unsigned int indices[6] = 
    {
        0, 1, 2, // Primeiro Triângulo
        2, 3, 0  // Segundo Triângulo
    };

    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    //-------------------------------------------------------------------

    glBindVertexArray(0);

    glBindVertexArray(vbo);

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
}