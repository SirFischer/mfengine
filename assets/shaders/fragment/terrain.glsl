#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in float zpos;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

//uniform vec3 lightPos;
uniform sampler2D texture1;

void main()
{
	vec3 lightPos = vec3(200, 100, 200);
	float ambientStrength = 0.05;
	vec3 lightColor = vec3(1.0, 1.0, 0.8);
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	
	FragColor = vec4(ambient + diffuse, 1.0) * texture(texture1, TexCoord);
	if (zpos < 0.7)
		FragColor = vec4(ambient + diffuse, 1.0) * vertexColor;
	if (zpos < 0.2)
		FragColor = vec4(ambient + diffuse, 1.0) * vec4(1, 1, 0, 1.0);
	if (zpos < 0)
		FragColor = vec4(ambient + diffuse, 1.0) * vec4(0, 0, 1, 1.0);
	if (zpos > 0.1)
		FragColor = vec4(ambient + diffuse, 1.0) * texture(texture1, TexCoord);
}