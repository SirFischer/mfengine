#version 330
 
in vec3 texCoord;
out vec4 fragColor;
uniform sampler2D texture1;
 
void main (void) {
    fragColor = texture(texture1, vec2(texCoord.x, texCoord.z));
}