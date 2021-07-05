#include "Class/HeaderProgram.h"

int main()
{
	Application window("Stencil Testing", 640, 480, true);

	// Shader
	Shader stencilShader("Files/Shaders/Shader27.shader");
	Shader cubeShader("Files/Shaders/Shader26.shader");

	// Objects
	float cubePos[] = 
    {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f, 
     0.5f,  0.5f, -0.5f, 
     0.5f,  0.5f, -0.5f, 
    -0.5f,  0.5f, -0.5f, 
    -0.5f, -0.5f, -0.5f, 

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f	
    };

    Buffer cubeObj(GL_ARRAY_BUFFER, cubePos, sizeof(cubePos));
    cubeObj.layout(3, 3 * sizeof(float), 0);

    // Transformations
    glm::vec3 camPos(0.0f, 0.0f, 4.0f);
    glm::vec3 camFront(0.0f, 0.0f, -1.0f);
    glm::vec3 camUp(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(camPos, camFront, camUp);

    glm::mat4 projection(1.0f);

	while(window.Execute())
	{
		window.Clear();

		//glEnable(GL_DEPTH_TEST);
		//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // se falhar, somente se o stencil passar, se o stencil e depth passarem 

		// 1 indica o valor a ser colocado no stencil buffer
		glStencilFunc(GL_ALWAYS, 1, 0xFF); // Todos os fragmentos irão modificar o stencil buffer
		// Habilitar a mudança nos pixels individuais
		glStencilMask(0xFF); // Ativar a mudança em todo o Stencil Buffer

		cubeShader.Use();
		
		glm::mat4 model(1.0f);
    	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / window.getHeight(), 0.1f, 100.0f);
		
		cubeShader.uniforfMat4fv("u_pvm", (float*)glm::value_ptr(projection * view * model));
		
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF); // Se o Pixel que irá ser pintado não for igual ao que se encontra no stencil buffer
		glStencilMask(0X00); // Desabilita a mudança de mascara
		glDisable(GL_DEPTH_TEST); // Desabilita o teste de profundidade

		stencilShader.Use();

		model = glm::scale(model, glm::vec3(1.05f, 1.05f, 1.05f));
		projection = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / window.getHeight(), 0.1f, 100.0f);
		
		cubeShader.uniforfMat4fv("u_pvm", (float*)glm::value_ptr(projection * view * model));
		
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glStencilMask(0XFF);
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glEnable(GL_DEPTH_TEST);

		window.Update();
	}
}