#include "Class/ShaderClass.h"

int main()
{
	GLFWwindow *window;

	if(!glfwInit())
	{
		show("Impossível Inicializar GLFW.");
		return -1;
	}

	window = glfwCreateWindow(640, 430, "Teste", NULL, NULL);

	if(!window)
	{
		show("Janela não criada.");
		return -1;
	}

	glfwMakeContextCurrent(window);

	// GLEW
	unsigned int status = glewInit();
	if(status != GLEW_OK)
	{
		show("Não foi possível inicializar GLEW.");
		return -1;
	}

	while(!glfwWindowShouldClose(window))	
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.3f, 1.0f);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}