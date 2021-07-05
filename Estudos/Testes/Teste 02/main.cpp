#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#define show(msg) std::cout << msg << std::endl

#include "Class/Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Camera Settings
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);

glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

int main()
{
	GLFWwindow *window;

	if(!glfwInit())
	{
		show("GLFW nao inicializado.");
		return -1;
	}

	const int width = 640;
	const int height = 480;

	window = glfwCreateWindow(width, height, "Utilizando Camera", nullptr, nullptr);
	if(!window)
	{
		show("Janela nao criada");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	//<<<<<| GLEW |>>>>>
	unsigned int status = glewInit();
	if(status != GLEW_OK)
	{
		show("GLEW nao inicializado.");
		glfwTerminate();
	}

	glViewport(0, 0, width, height);

	//<<<<<| DEFINIÇÕES |>>>>>

	// ====> [ Object ]

	float vertices[8] = 
	{
		-0.3f, -0.3f,
		 0.3f, -0.3f,
		 0.3f,  0.3f,
		-0.3f,  0.3f
	};

	unsigned int indices[6] = 
	{
		0, 1, 2,
		2, 3, 0
	};

	// Vertex Buffer
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	// Element Buffer Object
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ====> [ Shader ] 
	Shader shader("Shaders/shader1.shader");
	shader.Use();

	float colors[3] = {1.0f, 0.0f, 1.0f};
	shader.SetUniformf("u_color", 3, colors);

	// Variáveis Extras
	int i = 0;

	// =====> [ CURSOR ]
	unsigned char pixels[16 * 16 * 4];
	memset(pixels, 0xff, sizeof(pixels));

	pixels[0] = 0;

	GLFWimage image;
	image.width = 16;
	image.height = 16;
	image.pixels = pixels;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);
	if(!cursor)
		show("Cursor nao criado.");

	glfwSetCursor(window, cursor);

	double xpos, ypos, prev_xpos, prev_ypos;

	// =====> [ Visualização ]

	// Movimento
	float cameraSpeed = 0.05f;
	float vertical[2] = {0.0f, 0.0f};

	// Camera
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	//<<<<<| EXECUÇÃO |>>>>>
	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		shader.SetUniformMatrix4fv("u_move", glm::value_ptr(projection * view));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		if(glfwGetTime() > 0.06)
		{
			prev_xpos = xpos;
			prev_ypos = ypos;

			glfwGetCursorPos(window, &xpos, &ypos);

			if(xpos - prev_xpos > 0)
				cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			else if(xpos - prev_xpos < 0)
				cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

			if(ypos - prev_ypos > 0)
				cameraPos += glm::normalize(glm::cross(cameraFront, cameraRight)) * cameraSpeed;
			else if(ypos - prev_ypos < 0)
				cameraPos -= glm::normalize(glm::cross(cameraFront, cameraRight)) * cameraSpeed;

			glfwSetTime(0);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	glfwDestroyCursor(cursor);

	show("Janela Fechada.");
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	float cameraSpeed = 0.05f;
	if(key == GLFW_KEY_W)
		cameraPos += (cameraSpeed * cameraFront);
	if(key == GLFW_KEY_S)
		cameraPos -= (cameraSpeed * cameraFront);
	if(key == GLFW_KEY_A)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if(key == GLFW_KEY_D)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}