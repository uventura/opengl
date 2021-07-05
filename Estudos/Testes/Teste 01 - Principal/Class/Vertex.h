class Vertex
{
private:
	unsigned int m_ID = 0;
	unsigned int m_Index = 0;
	unsigned int m_Pointer = 0;
	unsigned int m_Type;

public:
	Vertex(unsigned int count, const float *data, unsigned int usage);
	~Vertex();

	void Layout(int size, unsigned int type);

	void Bind();
	void Unbind();
};