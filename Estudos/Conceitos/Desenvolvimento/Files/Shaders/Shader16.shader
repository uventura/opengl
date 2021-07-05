#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;

out vec2 fragTexCoords;

void main()
{
    gl_Position = vec4(position, 1.0f);
    fragTexCoords = texCoords;
}

#shader fragment
#version 330 core

out vec4 color;
in vec2 fragTexCoords;

uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, fragTexCoords);
    color = texColor;
}