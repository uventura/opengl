[vertex]
#version 450 core

layout (location = 0) in vec3 position;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position.xyz, 1.0f);
}

[fragment]
#version 450 core

uniform vec4 u_color;
out vec4 color;

void main()
{
	color = u_color;
}