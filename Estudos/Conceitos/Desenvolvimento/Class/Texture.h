#pragma once
#include "MainHeader.h"

#ifndef TEXTURE_CLASS
#define TEXTURE_CLASS

class Texture
{
private:
	unsigned int m_id;
	int m_width, m_height, m_bpp;

public:
	Texture(const char* src);
	~Texture();

	inline unsigned int id(){return m_id;};
	void bind(int slot = 0);
	void unbind();
	void Delete();
};

#endif