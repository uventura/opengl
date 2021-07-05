#include "Buffer.h"

Buffer::Buffer(int type, void* data, int size)
{
    if(type == GL_ARRAY_BUFFER || type == GL_ELEMENT_ARRAY_BUFFER)
    {   
        glGenBuffers(1, &m_id);
        m_layout = 0;
        m_type = type;

        m_data = data;
        m_size = size;

        bind();
        glBufferData(type, size, data, GL_STATIC_DRAW);
    }
    else
    {
        std::cout << "Buffer: [BUFFER ERROR] type undefined.\n";
        m_id = -1;
    }
}

void Buffer::layout(int count, int stride, void* offset)
{
    bind();
    if(m_id != -1)
    {
        glVertexAttribPointer(m_layout, count, GL_FLOAT, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(m_layout);

        ++m_layout;
    }
}

void Buffer::bind()
{
	if(m_id != -1)
    {
        glBindBuffer(m_type, m_id);
    }
	else
		std::cout << "Buffer: [BUFFER ERROR] Impossible bind element.\n";
}