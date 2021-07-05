#shader vertex
#version 450 core

layout (location = 0) in vec3 position;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position, 1.0f);
}

#shader fragment
#version 450 core

out vec4 color;
uniform vec3 objColor;
uniform vec3 lightColor;

void main()
{
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objColor;

    color = vec4(result * lightColor, 1.0f);
}