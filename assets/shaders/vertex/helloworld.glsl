#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 projection;

out vec4 vertexColor;

void main()
{
	gl_Position = projection * view * vec4(aPos, 1.0);
	vertexColor = vec4(0.5, 0.5, 0.5, 1.0);
	if (aPos[1] < 6)
		vertexColor = vec4(0, 1, 0, 1.0);
	if (aPos[1] < 1)
		vertexColor = vec4(1, 1, 0, 1.0);
	if (aPos[1] < 0)
		vertexColor = vec4(0, 0, 1, 1.0);
}