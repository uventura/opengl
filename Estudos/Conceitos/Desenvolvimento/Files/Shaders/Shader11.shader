#shader vertex
#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 Normal;

uniform mat4 global;
uniform mat4 model;

out vec3 fragPos;
out vec3 normal;
out mat4 modelFrag;

void main()
{
    gl_Position = global * model * vec4(position, 1.0f);
    fragPos = vec3(model * vec4(position, 1.0f)); // Posição de cada elemento
    normal = Normal; // Vetor normal de cada elemento
    modelFrag = model;
}

#shader fragment
#version 450 core
out vec4 color;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 objColor;
uniform float lightIntens;

in vec3 normal; // vetor normal
in vec3 fragPos; // Posição de cada fragmento
in mat4 modelFrag;

void main()
{
	// Cor do objeto no ambiente
	float strength = 0.1f;
	vec3 ambient = lightColor * strength;

	// Luz do objeto em todo o ambiente
	vec3 norm = normalize(mat3(transpose(inverse(modelFrag))) * normal); // Vetor normal normalizado.
	vec3 light_dir = normalize(lightPos - fragPos); // Vetor direção da luz.
	float intenDiffuse = max(dot(norm, light_dir), 0.0); // Quantidade de luz difundida.
	vec3 diffuse = intenDiffuse * lightColor + lightIntens;

	vec3 resultant = (ambient + diffuse) * objColor;

    color = vec4(resultant, 1.0f);
}