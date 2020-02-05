#version 330
 
in vec2 texCoord;
out vec4 fragColor;
uniform sampler2D texture1;

void main (void) {
    fragColor = texture(texture1, texCoord);
}
