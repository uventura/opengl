#shader vertex
#version 450 core

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
#version 450 core

struct spotlight
{
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
};	

uniform spotlight spot;

out vec4 color;
in vec3 v_normal;
in vec3 v_fragPos;

uniform vec3 u_eyePos;
uniform vec3 u_lightColor;
uniform vec3 u_objColor;

void main()
{
	vec3 lightDir = normalize(spot.position - v_fragPos);
	float theta = dot(lightDir, normalize(-spot.direction)); // cos do ângulo entre o vetor da luz e o vetor do spotlight.

	float epsilon = spot.cutOff - spot.outerCutOff;
	float intens = clamp((theta - spot.outerCutOff) / epsilon, 0.0f, 1.0f);

	// Ambient
	float lightStrength = 0.5;
	vec3 ambient = u_lightColor * lightStrength;

	//Diffuse
	vec3 vecNormal = normalize(v_normal);
	float percentDiffuse = max(dot(vecNormal, lightDir), 0.0f);
	vec3 diffuse = percentDiffuse * u_lightColor;

	// Specular
	float percentSpecular = 0.5f;
	vec3 lightDirRef = normalize(reflect(-lightDir, vecNormal));
	vec3 viewer = normalize(u_eyePos - v_fragPos);
	float specularIntens = pow(max(dot(lightDirRef, viewer), 0.0f), 64);
	vec3 specular =  specularIntens * u_lightColor;

	diffuse *= intens;
	specular *= intens;

	vec3 result = (ambient + diffuse + specular) * u_objColor;
	color = vec4(result, 1.0f);
}