/* Este shader foi utilizado com shader4.cpp*/

[vertex]
#version 450 core

/* Teste de comentário */

layout (location = 0) in vec2 positions;
out vec4 colors; /* Significa que está variável representará uma saída para o fragment*/

void main()
{
    gl_Position = vec4(positions.x, positions.y, 1.0f, 1.0f);
    colors = vec4(0.8f, 1.0f, 0.3f, 1.0f);
}

[fragment]
#version 450 core

out vec4 color;
in vec4 colors; /* Esta variável irá receber de um vertex*/

void main()
{
    color = colors;
}