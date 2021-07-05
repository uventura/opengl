#include <fstream>

#include <iostream>
#include <sstream>
#include <stdio.h>

#define show(msg) std::cout << msg << std::endl

//<<<<<<<<<<| SHADER FUNCTIONS |>>>>>>>>>>
enum type {NONE = -1, VERTEX = 0, FRAGMENT = 1};

struct shaderCode
{
	std::string vertex, fragment;
	const char *vertexPtr, *fragmentPtr;
};

shaderCode getShaderSource(std::string local){
	std::ifstream shaderSrc;
	shaderSrc.open(local);

	shaderCode src;
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

//<<<<<<<<<<| IMAGE FUNCTIONS |>>>>>>>>>>
struct ImageBMP
{
	unsigned char header[54];
	unsigned int width, height;
	unsigned int DataPosition; // Onde os dados começam
	unsigned int ImageSize;
	unsigned char *data;
};

ImageBMP LoadBMP(const char* local)
{
	ImageBMP img;

	FILE *file = fopen(local, "rb");
	if(!file)
	{
		std::cout << "Image not founded." << std::endl;
		img.ImageSize = 0;

		fclose(file);
		return img;
	}

	if(fread(img.header, 1, 54, file) != 54)
	{
		std::cout << "It's not BMP" << std::endl;

		fclose(file);
		return img;
	}

	if(img.header[0] != 'B' || img.header[1] != 'M')
	{
		std::cout << "It's not BMP" << std::endl;

		fclose(file);
		return img;
	}

	// Attribs
	img.DataPosition = *(int*)&(img.header[0X0A]);
	img.ImageSize = *(int*)&(img.header[0X22]);
	img.width = *(int*)&(img.header[0X12]);
	img.height = *(int*)&(img.header[0X16]);

	// Defintions
	if(img.ImageSize == 0) img.ImageSize = img.width * img.height * 3;
	if(img.DataPosition = 0) img.DataPosition = 54;

	img.data = new unsigned char [img.ImageSize];
	fread(img.data, 1, img.ImageSize, file);
		
	fclose(file);
	return img;
};