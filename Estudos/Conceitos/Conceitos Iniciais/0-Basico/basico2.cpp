#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "../includes/functions/mainFunc.cpp"

int main(void)
{
	GLFWwindow* window;

	if(!glfwInit()) return -1; // Verificar se a janela pode ser inicializada

	window = glfwCreateWindow(640, 480, " Basico 2 - Criando Triangulo com OpenGL Moderno", NULL, NULL); // Criar características da janela

	if(!window) // caso não possa criar janela
	{
		glfwTerminate(); // Encerra o GLFW
		return -1;
	}

	glfwMakeContextCurrent(window); // Criar Contexto da janela

	GLenum err = glewInit(); // Inicializar o GLEW
	if(GLEW_OK != err)
	{
		show("GLEW nao pode ser inicializado\n");
	}

	show("Versao do Glew: " << glewGetString(GLEW_VERSION));
	show("Versao do OpenGL: " << glGetString(GL_VERSION));

	/*<<<<<<<<<| Dados GLobais Utilizados |>>>>>>>>>*/
	GLfloat vertices[9] = {
		 0.0f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* De que maneira os dados estão estruturados no buffer */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	/*<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3); // Desenhar o buffer que está selecionado

		glfwSwapBuffers(window); // Obter Novas Atualizações
		glfwPollEvents(); // Verificar a ação de mouse, teclado ...
	}

	glfwTerminate();
}
