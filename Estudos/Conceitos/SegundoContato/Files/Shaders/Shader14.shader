// O código abaixo é uma variação do Shader11.shader
#shader vertex
#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 Normal;

uniform mat4 global;
uniform mat4 model;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 objColor;
uniform vec3 viewPos;
uniform float lightIntens;

out vec3 result;

void main(){
	vec4 pos = global * model * vec4(position, 1.0f);
    gl_Position = pos;
    vec3 fragPos = vec3(model * vec4(position, 1.0f)); // Posição de cada elemento

    // Ambient -> cor do ambiente com a baixa ausência de luz
    float strength = 0.3;
    vec3 ambient = lightColor * strength;

    // Diffuse -> Luz refletida do objeto no ambiente
    vec3 normal = normalize(mat3(transpose(inverse(model))) * Normal); // Vetor normal de cada elemento
    vec3 lightDir = normalize(lightPos - fragPos); // Direção da Luz
    float intenDiff = clamp(dot(normal, lightDir), 0.0, 1.0f); // Intensidade da difusão da luz
    vec3 diffuse = intenDiff * lightColor + lightIntens;

    // Specular -> Luz refletida para o observador
    float specPercent = 0.8f;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectViewDir = normalize(reflect(-viewDir, normal));
    float specInten = pow(max(dot(viewDir, reflectViewDir), 0.0), 128);
    vec3 specular = specPercent * specInten * lightColor;

    result = (ambient + diffuse + specular) * objColor;
}

#shader fragment
#version 450 core
out vec4 color;

in vec3 result;

void main(){
    color = vec4(result, 1.0f);
}
