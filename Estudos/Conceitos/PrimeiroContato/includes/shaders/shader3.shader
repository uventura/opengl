/* Este shader foi utilizado com shader4.cpp*/

[vertex]
#version 450

layout (location = 0) in vec2 position;

void main()
{
    gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
}

[fragment]
#version 450

out vec4 color;
uniform vec4 ourColor;

void main()
{
    color = ourColor;
}