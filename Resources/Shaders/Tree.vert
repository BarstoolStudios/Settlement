#version 430
uniform mat4 uMVP;
uniform mat3 uNormalMatrix;
uniform vec3 uSunDirection;
in vec3 iPosition;
in vec3 iNormal;
out vec3 oColor;
			
void main() {
	vec3 iColor = vec3(0,1,0);

	vec3 nNormal = uNormalMatrix * iNormal;

	vec3 diffuse = iColor * max(0.0, dot(normalize(nNormal), normalize(uSunDirection))) * 0.5;
	vec3 ambient = iColor * 0.5;

	oColor = diffuse + ambient;
	
	gl_Position = uMVP * vec4(iPosition, 1);
}