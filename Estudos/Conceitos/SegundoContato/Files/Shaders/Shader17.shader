#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 space;

out vec3 v_normal;
out vec3 v_fragPos;

void main()
{
	v_fragPos = vec3(model * vec4(position, 1.0f));
	v_normal = normalize(mat3(transpose(inverse(model))) * normal);

	gl_Position = space * vec4(v_fragPos, 1.0f);
}

#shader fragment
#version 330 core

out vec4 color;
in vec3 v_normal;
in vec3 v_fragPos;

uniform vec3 u_lightPos;
uniform vec3 u_eyePos;
uniform vec3 u_lightColor;
uniform vec3 u_objColor;

// Materials Settings
uniform vec3 u_ambient;
uniform vec3 u_diffuse;
uniform vec3 u_specular;
uniform float u_shine;

void main()
{
	// Ambient
	vec3 ambient = u_ambient * u_lightColor;

	//Diffuse
	vec3 vecNormal = normalize(v_normal);
	vec3 lightDir = normalize(u_lightPos - v_fragPos);
	float percentDiffuse = clamp(dot(vecNormal, lightDir), 0.0f, 1.0f);
	
	vec3 diffuse = percentDiffuse * u_lightColor * u_diffuse; // Sem u_diffuse, você obtém apenas o vetor das cores da luz, com u_diffuse você obtém a cor que o objeto irá difundir junto também com a cor do objeto que é cálculado mais a frente.

	// Specular
	float percentSpecular = 0.5f;
	vec3 lightDirRef = normalize(reflect(-lightDir, vecNormal));
	vec3 viewer = normalize(u_eyePos - v_fragPos);
	float specularIntens = pow(max(dot(lightDirRef, viewer), 0.0f), u_shine);
	vec3 specular =  u_specular * specularIntens * u_lightColor;

	vec3 result = (ambient + diffuse + specular) * u_objColor;
	color = vec4(result, 1.0f);
}