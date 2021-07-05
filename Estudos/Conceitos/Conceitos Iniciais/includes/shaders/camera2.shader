[vertex]

#version 450 core

layout (location = 0) in vec3 positions;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_persp;

void main()
{
    gl_Position = u_persp * u_view * u_model * vec4(positions, 1.0f);
}

[fragment]

#version 450 core

out vec4 color;

void main()
{
    color = vec4(0.8f, 0.0f, 0.8f, 1.0f);
}