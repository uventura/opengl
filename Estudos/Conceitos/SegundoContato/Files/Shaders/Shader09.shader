#shader vertex
#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 space;

out vec3 Normal;
out vec3 fragPos;

void main()
{
    gl_Position = space * model * vec4(position, 1.0f);
    fragPos = vec3(model * vec4(position, 1.0f));
    Normal = mat3(transpose(inverse(model))) * normal;
}

#shader fragment
#version 450 core

out vec4 color;

uniform vec3 lightColor;
uniform vec3 objColor;
uniform vec3 lightPos;
uniform vec3 eyePos;

in vec3 Normal;
in vec3 fragPos;

void main()
{
    float ambientStrenght = 0.3f;
    vec3 ambient = ambientStrenght * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5f;
    vec3 viewDir = normalize(fragPos - eyePos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objColor;

    color = vec4(result, 1.0f);
}