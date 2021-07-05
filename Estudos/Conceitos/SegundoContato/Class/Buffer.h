#include "MainHeader.h"

class Buffer
{
private:
	unsigned int m_id;
	unsigned int m_type;

	int m_layout;

	// Data Informations
	void* m_data;
	int m_size;

public:
	Buffer(int type, void* data, int size);

	inline unsigned int getBuffer(){return m_id;};
	void layout(int count, int stride, void* offset);

	void bind();
	inline void unbind(){glBindVertexArray(0);};
};
