#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

out vec4 vertexColor;
out float zpos;
out vec2 TexCoord;

void main()
{
	gl_Position = projection * view * transform * vec4(aPos, 1.0);
	vertexColor = vec4(0.1, 1.0, 0.1, 1.0);
	zpos = aPos[1];
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}