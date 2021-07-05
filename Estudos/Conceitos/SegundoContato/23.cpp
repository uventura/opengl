#include "Class/HeaderProgram.h"

int main()
{
	Application window("Depth Testing", 640, 480, true);

	glfwSetKeyCallback(window.getWindowPtr(), keyCamCallback);
    glfwSetScrollCallback(window.getWindowPtr(), scrollCamCallback);

	Shader shader("Files/Shaders/Shader25.shader");

	// Object
	float vertices[] = 
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	Buffer vbo(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
	vbo.layout(3, 3 * sizeof(float), 0);

	// Transformations
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Camera3D cam;
    glm::vec3 cameraPos;
    frontDir = cam.getVecFront();

    glm::mat4 persp(1.0f);

	while(window.Execute())
	{
		window.Clear();

		cam.setZoom(incrZoom);
        cam.setVecFront(frontDir);
        cam.moveCamera(keys);

        persp = glm::perspective(glm::radians(cam.getZoom()), (float)window.getWidth()/(float)window.getHeight(), 0.1f, 100.0f);
        cameraPos = cam.getCamPos();

        shader.Use();
        shader.uniforfMat4fv("u_projView", (float*)glm::value_ptr(persp * cam.getCamMatrix()));
        shader.uniforfMat4fv("u_model", glm::value_ptr(model));

		if(!modeCursor)
        {
            glfwSetInputMode(window.getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(window.getWindowPtr(), cursorCamCallback);
        }
        else
        {
            glfwSetInputMode(window.getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPosCallback(window.getWindowPtr(), nullptr);
        }

        vbo.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);

		window.Update();
	}
}