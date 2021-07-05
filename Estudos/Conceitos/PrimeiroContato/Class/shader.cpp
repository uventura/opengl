#pragma once

#include "shader.h"

Shader::Shader(const char *src)
{
    ShaderCode file = ShaderSource(src);
    
    // Vertex Shader;
    unsigned int Vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(Vertex, 1, &file.vertexPtr, NULL);
    glCompileShader(Vertex);

    // Fragment Shader
    unsigned int Fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(Fragment, 1, &file.fragmentPtr, NULL);
    glCompileShader(Fragment);

    // Shader Program
    ShaderID = glCreateProgram();
    glAttachShader(ShaderID, Vertex);
    glAttachShader(ShaderID, Fragment);
    glLinkProgram(ShaderID);

    // Errors
    GetMessageShaderError(Vertex, GL_VERTEX_SHADER);
    GetMessageShaderError(Fragment, GL_FRAGMENT_SHADER);

    int success, size;
    glGetProgramiv(ShaderID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramiv(ShaderID, GL_INFO_LOG_LENGTH, &size);

        char info[size];
        glGetProgramInfoLog(ShaderID, size, NULL, info);

        std::cout << "Program Error: " << info << std::endl;
    }

    glDeleteShader(Vertex);
    glDeleteShader(Fragment);
}

Shader::~Shader()
{
    glDeleteProgram(ShaderID);
}

ShaderCode Shader::ShaderSource(const char *local)
{
	std::ifstream shaderSrc;
	shaderSrc.open(local);

	ShaderCode src;
	src.vertex = "";
	src.fragment = "";
	src.vertexPtr = nullptr;
	src.fragmentPtr = nullptr;

	if(shaderSrc.is_open())
	{
		std::string line;
		type shaderType = type::NONE;

		while(getline(shaderSrc, line))
		{
			if(line.find("[vertex]") != -1) // Nunca se esqueça que o find retorna -1 caso não encontre
			{
				shaderType = type::VERTEX;
				continue;
			}
			else if(line.find("[fragment]") != -1)
			{
				shaderType = type::FRAGMENT;
				continue;
			}

			if(shaderType == type::VERTEX)
			{	
				src.vertex += line + "\n";
			}
			else if(shaderType == type::FRAGMENT)
			{
				src.fragment += line + "\n";
			}
		}

		src.vertexPtr = src.vertex.c_str();
		src.fragmentPtr = src.fragment.c_str();
	}
	else
	{
		show("Error to open the file.");
	}
	shaderSrc.close();

	return src;
}

void Shader::GetMessageShaderError(unsigned int shader, unsigned int type)
{
    int success, size;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);

        if(type == GL_VERTEX_SHADER)
            std::cout << "VERTEX ERROR: " << std::endl;
        else
            std::cout << "FRAGMENT ERROR: " << std::endl;
        
        char info[size];
        std::cout << info << std::endl;
    }
}

void Shader::Use()
{
    glUseProgram(ShaderID);
}