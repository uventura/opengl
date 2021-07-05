#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 transform;
uniform vec4 move;

void main()
{
    gl_Position = transform * vec4(position.x + move.x, position.y + move.y, 0.0f, 1.0f);
}

#shader fragment
#version 330 core

out vec4 color;

void main()
{
    color = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}