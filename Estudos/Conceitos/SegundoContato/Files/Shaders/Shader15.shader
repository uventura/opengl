// ESSE SHADER PERTENCE AO ARQUIVO 17.CPP QUE DEU ERRADO
#shader vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 fragTexCoord;
uniform mat4 trans;

void main()
{
	gl_Position = trans * vec4(position, 1.0f);	
	fragTexCoord = texCoord;
}

#shader fragment
#version 330 core

out vec4 color;
in vec2 fragTexCoord;

uniform sampler2D exitTexture;

void main()
{
	color = texture(exitTexture, fragTexCoord);
}