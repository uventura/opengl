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

    window = glfwCreateWindow(680, 420, "Titulo", NULL, NULL);
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



    //<<<<<<<<<<| EXECUÇÃO |>>>>>>>>>>
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // [Código Aqui]

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}