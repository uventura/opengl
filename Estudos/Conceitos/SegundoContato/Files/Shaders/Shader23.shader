// Shader do arquivo 22.cpp, considerando o uso de texturas

#shader vertex
#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoords;

uniform mat4 u_projView;
uniform mat4 u_model;

out vec3 v_normals;
out vec2 v_texCoords;
out vec3 v_fragmentPosition;

void main()
{
	gl_Position = u_projView * u_model * vec4(position, 1.0f);
	
	v_normals = mat3(transpose(inverse(u_model))) * normals;
	v_texCoords = texCoords;
	v_fragmentPosition = vec3(u_model * vec4(position, 1.0f));
}

#shader fragment
#version 450 core

out vec4 color;

in vec3 v_normals;
in vec2 v_texCoords;
in vec3 v_fragmentPosition;

struct Material
{
	 sampler2D texture_diffuse1;
	 sampler2D texture_diffuse2;
	 sampler2D texture_diffuse3;	 

	 sampler2D texture_specular1;
	 sampler2D texture_specular2;
};	 

uniform Material material;
uniform vec3 u_eyePosition;

void main()
{
	// Ambient
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * vec3(1.0f, 1.0f, 1.0f);

	// Diffuse
	vec3 normal = normalize(v_normals);
	vec3 lightDir = normalize(v_fragmentPosition - vec3(0.5f, 0.0f, -2.0f));
	float diffuseStrength = clamp(dot(lightDir, normal), 0.0f, 1.0f);
	vec3 diffuse = 3.0 * diffuseStrength * vec3(texture(material.texture_diffuse1, v_texCoords)) * vec3(texture(material.texture_diffuse2, v_texCoords)) * vec3(texture(material.texture_diffuse3, v_texCoords));

	// Specular
	float specularPercent = 0.5f;
	vec3 specularLight = reflect(-lightDir, normal);
	vec3 specularViewer = normalize(u_eyePosition - v_fragmentPosition);
	float specularStrength = pow(max(dot(specularLight, specularViewer), 0.0f), 64);
	vec3 specular = specularStrength * vec3(texture(material.texture_specular1, v_texCoords)) * vec3(texture(material.texture_specular2, v_texCoords));

	color = vec4(diffuse + specular, 1.0);
}