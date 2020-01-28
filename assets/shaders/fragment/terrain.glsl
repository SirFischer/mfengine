#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in float zpos;
in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, TexCoord);
	if (zpos < 0.7)
		FragColor = vertexColor;
	if (zpos < 0.2)
		FragColor = vec4(1, 1, 0, 1.0);
	if (zpos < 0)
		FragColor = vec4(0, 0, 1, 1.0);
	if (zpos > 0.1)
		FragColor = texture(texture1, TexCoord);
}