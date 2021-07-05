#include "Vertex.h"

#include <GL/glew.h>

Vertex::Vertex(unsigned int count, const float *data, unsigned int usage)
{
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(usage, vbo);
	glBufferData(usage, count, data, GL_STATIC_DRAW);

	m_ID = vbo;
	m_Type = usage;

	glBindBuffer(usage, 0);
}

Vertex::~Vertex()
{
	glBindBuffer(m_Type, 0);
}

void Vertex::Layout(int size, unsigned int type)
{
	glEnableVertexAttribArray(m_Index);
	glVertexAttribPointer(m_Index, size, type, GL_FALSE, GL_FLOAT, size * sizeof(float), (const void*)m_Pointer);

	m_Pointer++;
	m_Index++;
}

void Vertex::Bind()
{
	glBindBuffer(m_Type, m_ID);
}

void Vertex::Unbind()
{
	glBindBuffer(m_Type, 0);
}