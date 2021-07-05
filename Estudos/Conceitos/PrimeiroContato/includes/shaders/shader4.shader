/* Este Shader foi utilizado com o ex2.cpp*/

[vertex]
#version 450

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 colors;

out vec4 colorP;

void main()
{
    gl_Position = vec4(position.xy, 0.0f, 1.0f);
    colorP = vec4(colors.x, colors.y, colors.z, 1.0f);
}

[fragment]
#version 450

in vec4 colorP;
out vec4 color;

void main()
{
    color = colorP;
}