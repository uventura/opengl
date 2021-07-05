#include "Class/HeaderProgram.h"

int main()
{
	Application window("#Light #02 - Light Maps", 640, 480);
    Menu imgui(window.getWindowPtr());

	// Shader
	Shader paper("Files/Shaders/Shader19.shader");
    paper.Use();
    paper.uniform1iv("u_texture1", 0);
    paper.uniform1iv("u_texture2", 1);

	// Texture
	Texture diffuse("Files/Images/container2.png");
    Texture specular("Files/Images/container2_specular.png");

	// Object
    float vertices[] = 
    {
        // COORDS            // TEX COORDS  // NORMAL VECTORS
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,    0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,    0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f,    0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f,    0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };

    Buffer vbo(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    vbo.layout(3, 8 * sizeof(float), 0);
    vbo.layout(2, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vbo.layout(3, 8 * sizeof(float), (void*)(5 * sizeof(float)));

    Buffer ebo(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));

    // Light
    float lightMove[3] = {0.8f, 0.0f, 1.0f};
    float lightDir[3] = {0.0f, 0.0f, 1.0f};

	while(window.Execute())
	{
		window.Clear();

        paper.uniform3fv("u_lightPos", lightMove[0], lightMove[1], lightMove[2]);
        diffuse.bind();
        specular.bind(1);

        // Menu
        imgui.newFrame();
            ImGui::SliderFloat3("Light Position: ", lightMove, -1.0f, 1.0f);
        imgui.render();

        // Utilização da Câmera

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window.Update();
	}
}