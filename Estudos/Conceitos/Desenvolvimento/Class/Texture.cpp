#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Dep/stb_image.h"

Texture::Texture(const char* src)
{
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(src, &m_width, &m_height, &m_bpp, 4);

	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);		
		glBindTexture(0, m_id);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Could not Open the Image\n";
	}
}

Texture::~Texture()
{
	std::cout << "Fim do Escopo de Textura\n";
}

void Texture::bind(int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &m_id);
}