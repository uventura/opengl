[vertex]
#version 450 core

layout (location = 0) in vec3 position;
void main()
{
	glPosition = vec4(position.x, position.y, position.z, 1.0);
}

[fragment]
#version 450 core

out vec4 color;

void main()
{
	color = vec4(1.0f, 0.5f, 0.9f, 1.0f)
}