#version 430

uniform sampler2D uTexture;

in vec2 oTexCoord;

out vec4 fragColor;
			
void main() {
	fragColor = texture(uTexture, oTexCoord);
}