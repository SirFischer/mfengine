#version 330 core

#define MAX_LIGHTS	128 

out vec4 FragColor;

in vec4 vertexColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;

struct Light {    
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	int specular_pow;
};

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform int			lightNum;
uniform vec3		viewPos;
uniform Light		lights[MAX_LIGHTS];
uniform Material	material;
uniform int			hasTexture;

vec3		CalcLight(Light light, vec3 normal, vec3 fragpos)
{
	vec3 norm = normalize(normal);
	vec3 ambient = (light.ambient * material.ambient);
	light.diffuse = vec3(1.0) * (light.diffuse );
	light.specular = vec3(1.0) * (light.specular);
	vec3 lightdir = normalize(light.position - fragpos);
	vec3 diffuse = (max(dot(norm, lightdir), 0.0) / length(fragpos - light.position)) * (light.diffuse * material.diffuse);
	vec3 viewDir = normalize(viewPos - fragpos);
	vec3 reflectDir = reflect(-lightdir, norm);
	float flec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 spec = (flec * light.specular * material.specular);  /// length(fragpos - viewPos);
	return (ambient + diffuse + spec);
}

void main()
{
	vec3 result = vec3(0.0, 0.0, 0.0);
	for(int i = 0; i < lightNum && i < MAX_LIGHTS; i++)
        result += CalcLight(lights[i], Normal, FragPos);
	if (hasTexture == 1)
		FragColor = vec4(result, 1.0) * texture(texture1, TexCoord);
	else
		FragColor = vec4(result, 1.0);
	if (texture(texture1, TexCoord)[3] == 0)
		discard;
}
