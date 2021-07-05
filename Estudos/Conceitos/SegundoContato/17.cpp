// Esta tentativa deu errado, a segunda é o arquivo 18.cpp -> ERROR RESOLVIDO
#include "Class/HeaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Dep/stb_image.h"

int main()
{
	Application window("Textures #01", 640, 480, true);

	glfwSetKeyCallback(window.getWindowPtr(), keyCamCallback);
    glfwSetScrollCallback(window.getWindowPtr(), scrollCamCallback);

	// Shader
	Shader obj("Files/Shaders/Shader15.shader");

	// Texture
	int width, height, n;
	unsigned char* data = stbi_load("Files/Images/stones.jpg", &width, &height, &n, 4);

	show(width << " - " << height << "\n");

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Qual transformação aplicar em um eixo
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Tipo de renderição quando a imagem diminui
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// Mipmap são variados tamanhos de uma imagem que são chamados individualmente a medida que uma imagem
	// aumenta ou diminui, assim é uma melhor forma de otimização, abaixo encontra-se seu uso:
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Interpolará entre os mipmaps mais próximos e aplicará no resultado uma interpolação.
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // apenas irá aplicar uma interpolação no mipmap escolhido
	/*
		Variações:
			- GL_LINEAR_MIPMAP_LINEAR -> interpola entre texturas mipmap e aplica no resultado uma interpolação.
			- GL_NEAREST_MIPMAP_LINEAR -> interpola entre as texturas mipmap e aplica no resultado uma configuração do mais próximo.
			- GL_NEAREST_MIPMAP_NEAREST -> escolhe as textura mipmap mais próxima e aplica uma transformação do mais próximo e fará o mesmo no resultante.
			- GL_LINEAR_MIPMAP_NEAREST -> escole as texturas mais próximas no mipmap e aplicar no resultado uma interpolação
	
		*Para o aumento de imagem não se utiliza mipmaps, por isso simplesmente o uso de GL_LINEAR
	*/

	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		show("ERROR:: Could not load texture.\n");
	}
	stbi_image_free(data);

	// Object
	float vertices[] = {
     	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

	Buffer vbo(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
	vbo.layout(3, 5 * sizeof(float), 0);
	vbo.layout(2, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Transformations
	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	Camera3D cam;
    frontDir = cam.getVecFront();

	glm::mat4 persp(1.0f);

	while(window.Execute())
	{
		window.Clear();
		
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

		cam.setZoom(incrZoom);
		cam.setVecFront(frontDir);
		cam.moveCamera(keys);

		persp = glm::perspective(glm::radians(cam.getZoom()), (float)window.getWidth()/(float)window.getHeight(), 0.1f, 100.0f);

		vbo.bind();

		obj.Use();
		obj.uniform1iv("exitTexture", 0);
		obj.uniforfMat4fv("trans", (float*)glm::value_ptr(persp * cam.getCamMatrix() * model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		window.Update();
	}
}