#shader vertex

#version 450 core

in layout(location = 0) vec2 position;

void main()
{
	gl_Position = vec4(position.xy, 0.0f, 1.0f);
}

#shader fragment

#version 450 core

out vec4 color;
uniform vec4 ourColor;

void main()
{
	color = ourColor;
}
