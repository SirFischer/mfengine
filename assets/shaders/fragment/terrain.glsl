#version 330 core

#define MAX_LIGHTS	128 

out vec4 FragColor;

in vec4 vertexColor;
in float zpos;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

//uniform vec3 lightPos;
uniform sampler2D texture1;

struct Light {    
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform int		lightNum;
uniform Light	lights[MAX_LIGHTS];

vec3		CalcLight(Light light, vec3 normal, vec3 fragpos)
{
	vec3 norm = normalize(normal);
	vec3 diff = normalize(light.position - fragpos);
	vec3 res = (max(dot(norm, diff), 0.0) / length(fragpos - light.position)) * light.diffuse;
	return (light.ambient + res);
}

void main()
{
	vec3 result = vec3(0.0, 0.0, 0.0);
	for(int i = 0; i < lightNum && i < MAX_LIGHTS; i++)
        result += CalcLight(lights[i], Normal, FragPos);
	
	FragColor = vec4(result, 1.0) * texture(texture1, TexCoord);
	if (zpos < 0.7)
		FragColor = vec4(result, 1.0) * vertexColor;
	if (zpos < 0.2)
		FragColor = vec4(result, 1.0) * vec4(1, 1, 0, 1.0);
	if (zpos < 0)
		FragColor = vec4(result, 1.0) * vec4(0, 0, 1, 1.0);
	if (zpos > 0.1)
		FragColor = vec4(result, 1.0) * texture(texture1, TexCoord);
}
