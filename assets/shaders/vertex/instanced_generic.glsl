#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in mat4 instanceMatrix;

uniform mat4 view;
uniform mat4 projection;

out vec4 vertexColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
	gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0);
	FragPos = vec3(transform * vec4(aPos, 1.0));
	vertexColor = vec4(0.1, 1.0, 0.1, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	Normal = aNormal;
}