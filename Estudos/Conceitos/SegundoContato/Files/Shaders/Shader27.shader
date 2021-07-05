#shader vertex
#version 450 core

layout(location = 0) in vec3 position;

uniform mat4 u_pvm;

void main()
{
	gl_Position = u_pvm * vec4(position, 1.0f);
}

#shader fragment
#version 450 core

out vec4 color;

void main()
{
	color = vec4(0.4f, 0.3f, 0.3f, 1.0f);
}