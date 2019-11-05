#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 projection;

out vec4 vertexColor;

void main()
{
	gl_Position = projection * view * vec4(aPos, 1.0);
	vertexColor = vec4(aPos + 0.5, 1.0);
}