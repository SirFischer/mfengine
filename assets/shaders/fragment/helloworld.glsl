#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in float zpos;

void main()
{
	FragColor = vertexColor;
	if (zpos < 0.7)
		FragColor = vec4(0, 1, 0, 1.0);
	if (zpos < 0.2)
		FragColor = vec4(1, 1, 0, 1.0);
	if (zpos < 0)
		FragColor = vec4(0, 0, 1, 1.0);
}