// Este Shader é para complementar o Arquivo 22.cpp
// sendo que este não esta habilitado o uso de texturas

#shader vertex
#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_projView;
uniform mat4 u_model;

out vec3 v_fragPosition;
out vec3 v_normal;

void main()
{
	gl_Position = u_projView * u_model * vec4(position, 1.0f);
	
	v_fragPosition = vec3(u_model * vec4(position, 1.0f));
	v_normal = normal;
}

#shader fragment
#version 450 core

out vec4 color;

in vec3 v_fragPosition;
in vec3 v_normal;

void main()
{
	// Ambient
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * vec3(1.0f);

	// Diffuse
	vec3 normal = normalize(v_normal);
	vec3 diffuseLight = normalize(v_fragPosition - vec3(0.5f, 0.0f, -2.0f));
	float diffuseStrength = clamp(dot(normal, diffuseLight), 0.0f, 1.0f);
	vec3 diffuse = diffuseStrength * vec3(1.0f);

	color = vec4((ambient + diffuse) * vec3(0.3f, 0.2f, 0.25f), 1.0f);
}