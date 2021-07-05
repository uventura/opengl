#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "../includes/functions/mainFunc.cpp"

int main(void)
{
    GLFWwindow* window; // Ponteiro que descreve a janela

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate(); /* Finaliza a janela caso não foi possível inicializar */
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window); /* Criar o contexto atual da janela */

    GLenum err = glewInit();
	if(GLEW_OK != err) show("Erro ao inicializar\n");

	show("Sua versao do GLEW: " << glewGetString(GLEW_VERSION));
	show("A versao do Opengl: " << glGetString(GL_VERSION));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
    	glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
			glVertex2f(-0.5f, -0.5f);
			glVertex2f( 0.0f,  0.5f);
			glVertex2f( 0.5f, -0.5f);
		glEnd();

        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();

    
    return 0;
}