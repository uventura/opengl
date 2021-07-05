#include <iostream>
#include <vector>

enum ShaderType{VERTEX_SHADER, FRAGMENT_SHADER, NONE};

struct ShaderAttribs
{
	std::string source[2]; // source[0] -> Vertex Shader; source[1] -> Fragment Shader
	const char *vertexPtr, *fragmentPtr;
};

class Shader
{
private:
	ShaderAttribs m_Source;
	unsigned int m_ID;

	ShaderAttribs GetShaderSource(const char* src);

public:
	Shader(const char *src);
	~Shader();

	void Use();
	unsigned int Id();

	// Uniforms
	void SetUniformf(const char *uniformName, unsigned int count, const float *values);
	void SetUniformMatrix4fv(const char *uniform, const float* values);
};