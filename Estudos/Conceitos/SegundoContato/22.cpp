#include "Class/HeaderProgram.h"

int main()
{
	Application window("Mesh", 640, 480, true);

	glfwSetKeyCallback(window.getWindowPtr(), keyCamCallback);
    glfwSetScrollCallback(window.getWindowPtr(), scrollCamCallback);

	Shader shaderModelo("Files/Shaders/Shader24.shader");
	Model modelo("Files/Models/backpack/backpack.obj");

	//std::cout << modelo.textures_loaded.size() << "\n";

	// Transformations
    glm::mat4 model(1.0f);
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

        shaderModelo.Use();
        shaderModelo.uniforfMat4fv("u_projView", (float*)glm::value_ptr(persp * cam.getCamMatrix()));
        shaderModelo.uniforfMat4fv("u_model", glm::value_ptr(model));
        //shaderModelo.uniform3fv("u_eyePosition", cameraPos.x, cameraPos.y, cameraPos.z);

		modelo.Draw(shaderModelo);

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

		window.Update();
	}
}