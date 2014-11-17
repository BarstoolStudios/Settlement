#version 430

uniform mat4 uMVP;
uniform vec3 uColor;
uniform vec3 uSunDirection;
in vec3 iPosition;
in vec3 iNormal;
out vec3 oColor;

void main() {

	vec3 diffuse = uColor * max(0.0, dot(normalize(iNormal), normalize(uSunDirection))) * 0.5;
	vec3 ambient = uColor * 0.5;

	oColor = diffuse + ambient;
	
	gl_Position = uMVP * vec4(iPosition, 1);

}