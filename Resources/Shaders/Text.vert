#version 430

uniform mat3 uTransform;

in vec2 iPosition;
in vec2 iTexCoord;

out vec2 oTexCoord;
			
void main() {
	oTexCoord = iTexCoord;
	vec3 pos = uTransform * vec3(iPosition, 1);
	gl_Position = vec4(pos.xy, -1, 1);
}