#version 330

layout (location = 0) in vec3 aPos;

out vec3 texCoord;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
 
void main() {
    gl_Position = projection * view * transform * vec4(aPos, 1.0);
    texCoord = aPos;
}