#version 430

uniform mat4 uMVP;
uniform vec3 uSunDirection;
uniform mat3 uNormalMatrix;
uniform mat4[16] uBoneMatrices;
in vec3 iBoneWeights;
in vec3 iBoneIndices;
in vec3 iPosition;
in vec3 iNormal;
out vec3 oColor;

void main() {
    vec4 newPosition = vec4(0,0,0,0);
    vec4 newNormal = vec4(0,0,0,0);
    
	int index;
	for(int i = 0; i < 3; i++) {
	    if((index = int(iBoneIndices[i])) != -1) {
	        newPosition += (uBoneMatrices[index] * vec4(iPosition, 1)) * iBoneWeights[i];
	        newNormal += (uBoneMatrices[index] * vec4(iNormal, 0)) * iBoneWeights[i];;
	    }else {
	        break;
	    }
    }

	vec3 iColor = vec3(1, 0, 1);
    
    if(int(iBoneIndices[0]) != -1) {
    	vec3 normNormal = normalize(uNormalMatrix * vec3(newNormal));
    	vec3 diffuse = iColor * max(0.0, dot(normNormal, normalize(uSunDirection)));
    	vec3 ambient = iColor * 0.5;
    	oColor = ambient + diffuse;
    	
    	gl_Position = uMVP * vec4(newPosition.xyz, 1);
    }else {
     	vec3 normNormal = normalize(uNormalMatrix * vec3(iNormal));
    	vec3 diffuse = iColor * max(0.0, dot(normNormal, normalize(uSunDirection)));
    	vec3 ambient = iColor * 0.5;
    	oColor = ambient + diffuse;
    	
    	gl_Position = uMVP * vec4(iPosition, 1);
    }
}