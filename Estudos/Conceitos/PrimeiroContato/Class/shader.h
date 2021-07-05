#pragma once

#include <GL/glew.h>

#include <iostream>
#include <fstream>

class Shader{
private:
    ShaderCode ShaderSource(const char *src);
    unsigned int ShaderID;

    void GetMessageShaderError(unsigned int shader, unsigned int type);

public:
    Shader(const char *src);
    ~Shader();

    void Use();
};