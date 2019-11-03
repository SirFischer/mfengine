#version 330 core

uniform	float rel;

const vec3 palette[3] = vec3[3](
  vec3(-0.5, 0.5, 1.0),
  vec3(0.0, -0.5, 1.0),
  vec3(0.5, 0.5, 1.0)
);

void main()
{
	vec3 current = palette[gl_VertexID];
	current[1] += rel;
	current[0] += cos(asin(rel));
	gl_Position = vec4(current, 1.0);
}