#shader vertex
#version 450 core
layout (location = 0) in vec2 position;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position, 1.0f, 1.0f);
}

#shader fragment
#version 450 core

out vec4 color;
uniform vec4 u_color;

void main()
{
    color = u_color;
}