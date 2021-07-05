#pragma once
#include "MainHeader.h"

struct ShaderSource
{
	std::string VertexShader;
	std::string FragmentShader;
};

enum class ShaderType{NONE = -1, VERTEX = 0, FRAGMENT = 1};

class Shader
{
private:
	unsigned int m_shaderProgram;

	unsigned int CompileShader(const std::string& src, unsigned int type);
	ShaderSource GetShaderFiles(const std::string& src);

public:
	Shader(const std::string& src);
	~Shader();

	inline void Use(){ glUseProgram(m_shaderProgram); };
	inline unsigned int id(){ return m_shaderProgram; };

	void uniform4fv(const char* u_name, float v1, float v2, float v3, float v4);
	void uniform3fv(const char* u_name, float v1, float v2, float v3);
	void uniform1fv(const char* u_name, float v1);
	void uniform1iv(const char* u_name, int v1);
	void uniforfMat4fv(const char* u_name, float* values); // é uniform, mas outros programas dependem q seja uniforf, desculpa kkkkkkkk
};