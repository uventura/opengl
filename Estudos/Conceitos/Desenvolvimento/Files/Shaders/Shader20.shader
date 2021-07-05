// Esse foi o Shader teste do Programa 20.cpp para juntar duas texturas
#shader vertex
#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texPosition;
layout (location = 2) in vec3 normalVectors;

out vec2 v_texPosition;
out vec3 v_normalVectors;
out vec3 v_fragmentPos;

void main()
{
	gl_Position = vec4(position, 1.0f);
	v_texPosition = texPosition;
}

#shader fragment
#version 450 core

out vec4 color;
in vec2 v_texPosition;

uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

void main()
{
	color = mix(texture(u_texture1, v_texPosition), texture(u_texture2, v_texPosition), 0.3);
}