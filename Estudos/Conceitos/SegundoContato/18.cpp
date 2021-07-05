#include "Class/HeaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Dep/stb_image.h"

int main()
{
    Application window("Textures #02", 640, 480, true);

    // Shader
    Shader obj("Files/Shaders/Shader16.shader");

    // Texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(1);
    int width, height, bpp;
    unsigned char* data = stbi_load("Files/Images/mario.png",&width, &height, &bpp, 4);

    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(0, texture);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "STBI ERROR:: Could not load image.\n";
    }

    // Object
    float vertices[] = 
    {
        // COORDS           // TEX COORDS
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int vbo, ebo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    // Texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(1, texture);

    obj.Use();
    obj.uniform1iv("u_Texture", 0);

    while(window.Execute())
    {
        window.Clear();
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.Update();
    }

    glDeleteTextures(1, &texture);
}