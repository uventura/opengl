/* Este shader foi utilizado com texture1.cpp*/

[vertex]
#version 450

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoordLayout;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(position, 0.0f, 1.0f);
    TexCoord = texCoordLayout;
}

[fragment]
#version 450

out vec4 color;

in vec2 TexCoord;
uniform sampler2D u_tex;

void main()
{
    vec4 texColor = texture(u_tex, TexCoord);
    color = texColor;
}