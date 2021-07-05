#shader vertex
#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texPosition;
layout (location = 2) in vec3 normalVectors;

out vec2 v_texPosition;
out vec3 v_normalVectors;
out vec3 v_fragmentPos;

void main()
{
	gl_Position = vec4(position, 1.0f);
	v_texPosition = texPosition;
	v_normalVectors = normalVectors;
	v_fragmentPos = position;
}

#shader fragment
#version 450 core

out vec4 color;

in vec2 v_texPosition;
in vec3 v_normalVectors;
in vec3 v_fragmentPos;

uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform vec3 u_lightPos;

void main()
{
	// Ambient
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * vec3(1.0f, 1.0f, 1.0f);

	// Diffuse
	vec3 normal = normalize(v_normalVectors);
	vec3 lightDir = normalize(v_fragmentPos - u_lightPos);
	float diffuseStrength = clamp(dot(lightDir, normal), 0.0f, 1.0f);
	vec3 diffuse = diffuseStrength * vec3(1.0f, 1.0f, 1.0f) * vec3(texture(u_texture1, v_texPosition));

	// Specular
	float specularPercent = 0.5f;
	vec3 lightDirEye = normalize(reflect(-lightDir, normal));
	vec3 eyePos = normalize(vec3(0.0f, 0.0f, 1.5f) - v_fragmentPos);
	float specularIntens = pow(max(dot(lightDirEye, eyePos), 0.0f), 64);
	vec3 specular = specularIntens * vec3(1.0f, 1.0f, 1.0f) * vec3(texture(u_texture2, v_texPosition));

	// Result
	vec3 objColor = (ambient + diffuse + specular) * vec3(1.0f, 1.0f, 1.0f);

	color = vec4(objColor, 1.0f);
}