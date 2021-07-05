[vertex]

#version 450 core

layout (location = 0) in vec3 position;

uniform mat4 transform; // Definindo uma matriz de transformação

void main()
{
    gl_Position = transform * vec4(position.x, position.y, position.z, 1.0f);
}

[fragment]

#version 450 core

out vec4 color;
void main()
{
    color = vec4(0.6f, 0.0f, 0.6f, 1.0f);
}