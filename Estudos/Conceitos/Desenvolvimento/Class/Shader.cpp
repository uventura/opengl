#include "Shader.h"

Shader::Shader(const std::string& shaderPath)
{
	ShaderSource files = GetShaderFiles(shaderPath);
	unsigned int vShader = CompileShader(files.VertexShader, GL_VERTEX_SHADER);
	unsigned int fShader = CompileShader(files.FragmentShader, GL_FRAGMENT_SHADER);

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vShader);
	glAttachShader(m_shaderProgram, fShader);
	glLinkProgram(m_shaderProgram);
	glValidateProgram(m_shaderProgram);

	int sucess, size;
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &sucess);

	if(!sucess)
	{
		glGetProgramiv(m_shaderProgram, GL_INFO_LOG_LENGTH, &size);

		char info[size];
		glGetProgramInfoLog(m_shaderProgram, sizeof(info), nullptr, info);

		std::cout << "Program Error: " << info << "\n";

		m_shaderProgram = 0;
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_shaderProgram);
}

ShaderSource Shader::GetShaderFiles(const std::string& src)
{
	std::ifstream file(src);

	ShaderType type = ShaderType::NONE;
	std::stringstream shaderCode[2];

	if(file.is_open())
	{
		std::string line;
		while(getline(file, line))
		{
			if(line.find("#shader") != std::string::npos)
			{
				if(line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if(line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else if(type != ShaderType::NONE)
			{
				shaderCode[(int)type] << line << "\n";
			}
		}
	}
	else
	{
		std::cout << " >> [GET SHADER ERROR] Couldn't open the shader file." << "\n";
		return {"", ""};
	}

	return {shaderCode[0].str(), shaderCode[1].str()};
}

unsigned int Shader::CompileShader(const std::string& src, unsigned int type)
{
	const char* ptrSrc = src.c_str();

   	unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &ptrSrc, NULL);
	glCompileShader(id);

	int sucess, size;
	glGetShaderiv(id, GL_COMPILE_STATUS, &sucess);
	
	if(!sucess)
	{
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &size);

		char info[size];
		glGetShaderInfoLog(id, sizeof(info), nullptr, info);

		std::string typeShader = type == GL_VERTEX_SHADER? "Vertex Shader": "Fragment Shader";
		std::cout << " >> " << "[COMPILE SHADER ERROR] - " << typeShader << ": "<< info;

		return 0;
	}

	return id;
}

void Shader::uniform4fv(const char* u_name, float v1, float v2, float v3, float v4)
{
	int uniform = glGetUniformLocation(m_shaderProgram, u_name);

	if(uniform == -1)
		std::cout << "Shader: [UNIFORM] uniform not defined.\n";
	else
		glUniform4f(uniform, v1, v2, v3, v4);
}

void Shader::uniform3fv(const char* u_name, float v1, float v2, float v3)
{
	int uniform = glGetUniformLocation(m_shaderProgram, u_name);

	if(uniform == -1)
		std::cout << "Shader: [UNIFORM] uniform not defined.\n";
	else
		glUniform3f(uniform, v1, v2, v3);
}

void Shader::uniform1fv(const char* u_name, float v1)
{
	int uniform = glGetUniformLocation(m_shaderProgram, u_name);

	if(uniform == -1)
		std::cout << "Shader: [UNIFORM] uniform not defined.\n";
	else
		glUniform1f(uniform, v1);
}

void Shader::uniform1iv(const char* u_name, int v1)
{
	int uniform = glGetUniformLocation(m_shaderProgram, u_name);

	if(uniform == -1)
		std::cout << "Shader: [UNIFORM] uniform not defined.\n";
	else
		glUniform1i(uniform, v1);
}

void Shader::uniforfMat4fv(const char* u_name, float* values)
{
	int uniform = glGetUniformLocation(m_shaderProgram, u_name);
	
	if(uniform == -1)
		std::cout << "Shader: [UNIFORM] uniform not defined.\n";
	else
		glUniformMatrix4fv(uniform, 1, GL_FALSE, values);
}