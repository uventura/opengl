#include <GL/glew.h>

#include "Shader.h"
#include <fstream>

Shader::Shader(const char *src)
{
	m_Source = GetShaderSource(src);

	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &m_Source.vertexPtr, NULL);
	glCompileShader(vertex);
	
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &m_Source.fragmentPtr, NULL);
	glCompileShader(fragment);

	// Errors
	int success;

		// Vertex Error
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			int size;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &size);

			char info[size];
			glGetShaderInfoLog(vertex, size, 0, info);

			std::cout << "[VERTEX SHADER]:\n" << info << std::endl;
		}
		// Fragment Error
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			int size;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &size);

			char info[size];
			glGetShaderInfoLog(fragment, size, 0, info);

			std::cout << "[FRAGMENT VERTEX]:\n" << info << std::endl;
		}

	// Shader Program
	unsigned int shader = glCreateProgram();
	glAttachShader(shader, vertex);
	glAttachShader(shader, fragment);
	glLinkProgram(shader);

	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if(!success)
	{
		int size;
		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &size);

		char info[size];
		glGetProgramInfoLog(shader, size, 0, info);

		std::cout << "[SHADER PROGRAM ERROR]:\n" << info << std::endl;
	}

	m_ID = shader;

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glUseProgram(0);
}

Shader::~Shader()
{
	glUseProgram(0);
}

ShaderAttribs Shader::GetShaderSource(const char *src)
{
	ShaderAttribs shaderFile;
	shaderFile.source[ShaderType::VERTEX_SHADER] = "";
	shaderFile.source[ShaderType::FRAGMENT_SHADER] = "";

	std::ifstream file;

	file.open(src);

	if(file.is_open())
	{
		ShaderType type = NONE;
		std::string line;

		while(getline(file, line))
		{
			if(line.find("[vertex]") != -1)
			{
				type = VERTEX_SHADER;
				continue;
			}

			else if(line.find("[fragment]") != -1)
			{
				type = FRAGMENT_SHADER;
				continue;
			}

			if(type != NONE)
				shaderFile.source[type] += line + "\n";
		}

		shaderFile.vertexPtr = &shaderFile.source[ShaderType::VERTEX_SHADER][0];
		shaderFile.fragmentPtr = &shaderFile.source[ShaderType::FRAGMENT_SHADER][0];

		return shaderFile;
	}
	else
	{
		file.close();
		std::cout << "Can't open the file: " << src << std::endl;
	}

	file.close();
}

void Shader::Use()
{
	glUseProgram(m_ID);
}

void Shader::SetUniformf(const char *uniformName, unsigned int count, const float *values)
{
	int uniform = glGetUniformLocation(m_ID, uniformName);

	if(uniform == -1)
	{
		std::cout << "[UNIFORM ERROR]: \n" << "  Can't find uniform." << std::endl;
	}

	if(count == 1)
		glUniform1fv(uniform, 1, values);
	else if(count == 2)
		glUniform2fv(uniform, 1, values);
	else if(count == 3)
		glUniform3fv(uniform, 1, values);
	else if(count == 4)
		glUniform4fv(uniform, 1, values);
	else
		std::cout << "[UNIFORM ERROR]: \n" << "  Uniform with so much elements." << std::endl;
}

void Shader::SetUniformMatrix4fv(const char *uniformName, const float *values)
{
	int uniform = glGetUniformLocation(m_ID, uniformName);

	if(uniform == -1)
		std::cout << "[UNIFORM ERROR]: \n" << "  Uniform Matrix 4 not founded." << std::endl;

	glUniformMatrix4fv(uniform, 1, GL_FALSE, values);
}