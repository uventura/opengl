// Segunda Abordagem de Manipulação de Shaders

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Class/TimerClass.h"

static void ParseShader(const std::string& filepath)
{
	Timer t;

	std::ifstream stream(filepath);// arquivo oara ler valores(por isso ifstream)

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];

	ShaderType type = ShaderType::NONE;

	while(getline(stream, line))
	{
		if(line.find("#shader") != std::string::npos)
		{
			if(line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if(line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}

	stream.close();
}

int main()
{
	ParseShader("Files/Shaders/Shader02.shader");
}