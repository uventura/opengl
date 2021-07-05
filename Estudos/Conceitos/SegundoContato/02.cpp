// Primeira Abordagem de Manipulação de Shaders

#include <iostream>
#include <fstream>
#include <sstream>

#include "Class/TimerClass.h"

#define show(msg) std::cout << msg << "\n"

enum TypeShader{None = -1, VertexShader = 0, FragmentShader = 1};

struct ShaderFile
{
	std::string file[2];
};

int main()
{
	Timer t;
	std::fstream file;
	file.open("Files/Shaders/Shader01.shader");

	ShaderFile source;

	std::string line;
	TypeShader type = None;

	if(file.is_open())
	{
		while(getline(file, line))
		{
			// utilizar std::string::npos ao invés de -1
			if(line.find("<vertexshader>") != -1)
			{
				type = VertexShader;
				continue;
			}
			else if(line.find("<fragmentshader>") != -1)
			{
				type = FragmentShader;
				continue;
			}

			if(type > None)
				source.file[type].append(line + "\n");
		}
	}

	file.close();
}