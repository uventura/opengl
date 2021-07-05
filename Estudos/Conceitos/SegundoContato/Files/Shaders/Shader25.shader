#shader vertex
#version 450 core

layout(location = 0) in vec3 position;

uniform mat4 u_projView;
uniform mat4 u_model;

void main()
{
	gl_Position = u_projView * u_model * vec4(position, 1.0f);
}

#shader fragment
#version 450 core

out vec4 color;

float near = 0.1;
float far = 100.0;

float LinearizeDepth(float depth)
{
	float z = depth * 2.0 - 1.0;
	return (2.0 * near * far) / (near + far - z * (far - near));
}

void main()
{
	float depth = LinearizeDepth(gl_FragCoord.z) / far;

	color = vec4(vec3(depth), 1.0f);
}