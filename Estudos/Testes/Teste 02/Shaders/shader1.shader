[vertex]
#version 450 core

layout (location = 0) in vec2 position;

uniform mat4 u_move;

void main()
{
	gl_Position =  u_move * vec4(position.x, position.y, 0.0f, 1.0f);
}

[fragment]
#version 450 core

uniform vec3 u_color;
out vec4 color;

void main()
{
	color = vec4(u_color, 1.0f);
}