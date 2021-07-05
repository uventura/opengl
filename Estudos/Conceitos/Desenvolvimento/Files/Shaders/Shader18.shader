#shader vertex
#version 450 core

layout(location = 0) in vec3 position;

uniform mat4 trans;

void main()
{
	gl_Position = trans *  vec4(position, 1.0f);	
}

#shader fragment
#version 450 core

out vec4 color;
uniform vec3 u_lightColor;

void main()
{
	color = vec4(u_lightColor, 1.0f);	
}