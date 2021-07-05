// Desenhando Pontos
#include "Class/ShaderClass.h"

int main()
{
	GLFWwindow* window;

	if(!glfwInit())
	{
		show("GLFW not init.");
		return -1;
	}

	window = glfwCreateWindow(640, 480, "Points", NULL, NULL);
	if(!window)
	{
		show("Window not created.");
		return -1;
	}

	glfwMakeContextCurrent(window);

	// GLEW
	unsigned int status = glewInit();
	if(status != GLEW_OK)
	{
		show("Glew not init.");
		return -1;
	}

	// DATA
	float vertices[] = 
	{
		 0.0f,  0.0f,
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.0f,  0.5f,
		 1.0f, -1.0f,
		 0.3f,  0.3f
	};

	unsigned int vao;
	glGenVertexArrays(1, &vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(vao);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	Shader program("Files/Shaders/Shader02.shader");
	program.Use();

	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementos), elementos, GL_STATIC_DRAW);

	int vColor_loc = 1;
	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1f, 0.1, 0.15f, 1.0f);

		glBindVertexArray(vao);
		glVertexAttrib3f(vColor_loc, 1.0, 0.0, 0.0); // atribui valores para um vértice genérico.
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Existem: GL_POINTS, GL_LINES, GL_LINE_STRIP e GL_LINE_LOOP

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}