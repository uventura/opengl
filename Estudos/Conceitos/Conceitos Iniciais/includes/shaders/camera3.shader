[vertex]
#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color_att;

out vec3 color_frag;
uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position,  1.0f);
    color_frag = color_att;
}

[fragment]

#version 450 core

out vec4 color;
in vec3 color_frag;

void main()
{
    color = vec4(color_frag, 1.0f);
}