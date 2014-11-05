/******************************************************************************\
* File: ShaderUtil.cpp
*
* Author: Josh Taylor
*
* Header: ShaderUtil.h
*
* Description: Provides funtions to simplify interations with OpenGL shaders
\******************************************************************************/

#include <GL/glew.h>
#include "Util/ShaderUtil.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Util/GLMath.h"
#include "Models/Face.h"
#include "Models/Skeleton.h"
#include "Util/Utility.h"
#include "Util/lodepng.h"
#include "Util/GameTimer.h"

//==============================================================================
// Loads and Compiles Shader with openGL and Returns Handle to Shader
//==============================================================================
GLint ShaderUtil::loadShader(GLenum type, std::string shaderCode) {
	GLint shader = glCreateShader(type);

	const char* str = shaderCode.c_str();

	glShaderSource(shader, 1, &str, NULL);

	glCompileShader(shader);

	return shader;
}

//==============================================================================
// Reads Shader from a Shader File and Returns the String of Characters
//==============================================================================
std::string ShaderUtil::readShaderFromFile(std::string shaderName) {
	std::string text = "";
	std::string line = "";

	std::ifstream shaderFile(std::string("Resources/Shaders/") + shaderName);

	if (shaderFile.is_open()) {
		while (std::getline(shaderFile, line)) {
			text = text + line + '\n';
		}
		shaderFile.close();
	
	}else {
		std::cout << "Unable to read " << shaderName << '\n';
	}
	return text;
}

//==============================================================================
// Creates a Shader Program with openGL based on What Shaders are Used
//==============================================================================
GLint ShaderUtil::createProgram(std::string modelName, std::vector<GLenum> shaders, bool printStatus) {
	std::string header = std::string(7, '-') + ' ' + modelName + " Shaders " + std::string(7, '-');

	if(printStatus)
		Utility::printToOutput(header + '\n');

	GLint shaderProgram = glCreateProgram();

	for (int i = 0; i < shaders.size(); i++) {
		switch (shaders[i]) {
		
		case GL_VERTEX_SHADER: {
			std::string vertCode = readShaderFromFile(modelName + ".vert");
			GLint vertexShader = loadShader(GL_VERTEX_SHADER, vertCode);
			glAttachShader(shaderProgram, vertexShader);
			if (printStatus)
				printShaderStatus("Vertex", vertexShader);
			break;
		}

		case GL_FRAGMENT_SHADER: {
			std::string fragCode = readShaderFromFile(modelName + ".frag");
			GLint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragCode);
			glAttachShader(shaderProgram, fragmentShader);
			if (printStatus)
				printShaderStatus("Fragment", fragmentShader);
			break;
		}

		case GL_TESS_CONTROL_SHADER: {
			std::string tescCode = readShaderFromFile(modelName + ".tesc");
			GLint tessControlShader = loadShader(GL_TESS_CONTROL_SHADER, tescCode);
			glAttachShader(shaderProgram, tessControlShader);
			if (printStatus)
				printShaderStatus("Tessellation Control", tessControlShader);
			break;
		}

		case GL_TESS_EVALUATION_SHADER: {
			std::string teseCode = readShaderFromFile(modelName + ".tese");
			GLint tessEvaluationShader = loadShader(GL_TESS_EVALUATION_SHADER, teseCode);
			glAttachShader(shaderProgram, tessEvaluationShader);
			if (printStatus)
				printShaderStatus("Tessellation Evaluation", tessEvaluationShader);
			break;
		}

		case GL_GEOMETRY_SHADER: {
			std::string geomCode = readShaderFromFile(modelName + ".geom");
			GLint geometryShader = loadShader(GL_GEOMETRY_SHADER, geomCode);
			glAttachShader(shaderProgram, geometryShader);
			if (printStatus)
				printShaderStatus("Geometry", geometryShader);
			break;
		}
		}
	}

	glLinkProgram(shaderProgram);

	printProgramStatus(shaderProgram);

	if(printStatus)
		Utility::printToOutput(std::string(header.size(), '-') + '\n');

	return shaderProgram;
}

//==============================================================================
// Loads PNG with lodepng and Creates a Texture. Returns Texture Handle
//==============================================================================
GLuint ShaderUtil::loadPNG(std::string pngName) {
	std::vector<unsigned char> image;
	unsigned width;
	unsigned height;
	unsigned error;

	GLuint textureHandle;
	glGenTextures(1, &textureHandle);

	if(textureHandle < 0) {
		Utility::printToOutput(std::string("Failed to Generate Texture Handle: ") + pngName + '\n');
	}

	error = lodepng::decode(image, width, height, std::string("Resources/Textures/") + pngName);

	if(error != 0) {
		Utility::printToOutput(std::string("Failed to Decode: ") + pngName + '\n');
		exit(-1);
	}

	glBindTexture(GL_TEXTURE_2D, textureHandle);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(image[0]));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	return textureHandle;
}

//==============================================================================
// Loads a Barstool Studios Model File (.bar)
//==============================================================================
ModelData ShaderUtil::loadModel(std::string modelName) {
	std::string line = "";

	std::vector<Vector3f> vertices;
	std::vector<Vector3f> normals;
	std::vector<Vector2f> texCoords;
	std::vector<Vector3f> weights;
	std::vector<Vector3f> weightIndices;
	std::vector<Face> faces;

	std::ifstream modelFile(std::string("Resources/Models/") + modelName + ".bar");

	Skeleton* skeleton = NULL;

	if(modelFile.is_open()) {

		while(std::getline(modelFile, line)) {
			
			// Process vertex position
			if(Utility::stringStartsWith(line, "v ")) {
				std::vector<std::string> split;
				Utility::stringSplit(line, ' ', split);

				vertices.push_back(Vector3f(std::stof(split[1]), std::stof(split[2]), std::stof(split[3])));

				// If model has Skeleton then read in weights
				if(skeleton != NULL) {
					Vector3f w(0, 0, 0);
					Vector3f ids(-1, -1, -1);

					// Max of three bones. May be less
					if(split.size() > 4) {
						ids.x = skeleton->getBoneID(split[4]);
						w.x = std::stof(split[5]);
						if(split.size() > 6) {
							ids.y = skeleton->getBoneID(split[6]);
							w.y = std::stof(split[7]);
							if(split.size() > 8) {
								ids.z = skeleton->getBoneID(split[8]);
								w.z = std::stof(split[9]);
							}
						}
					}

					weights.push_back(w);
					weightIndices.push_back(ids);
				}
			}

			// Process vertex normal
			else if(Utility::stringStartsWith(line, "vn ")) {
				std::vector<std::string> split;
				Utility::stringSplit(line, ' ', split);

				normals.push_back(Vector3f(std::stof(split[1]), std::stof(split[2]), std::stof(split[3])));
			}

			// Process vertex texture coordinate
			else if(Utility::stringStartsWith(line, "vt ")) {
				std::vector<std::string> split;
				Utility::stringSplit(line, ' ', split);

				texCoords.push_back(Vector2f(std::stof(split[1]), std::stof(split[2])));
			}
			
			// Process face
			else if(Utility::stringStartsWith(line, "f ")) {
				std::vector<std::string> split;
				Utility::stringSplit(line, ' ', split);

				std::vector<std::string> v1;
				std::vector<std::string> v2;
				std::vector<std::string> v3;

				Utility::stringSplit(split[1], '/', v1);
				Utility::stringSplit(split[2], '/', v2);
				Utility::stringSplit(split[3], '/', v3);

				if(v1[1] == "") {
					int vertIndices[] {std::stof(v1[0]), std::stof(v2[0]), std::stof(v3[0])};
					int normIndices[] {std::stof(v1[2]), std::stof(v2[2]), std::stof(v3[2])};

					faces.push_back(Face(vertIndices, normIndices));

				} else {
					int vertIndices[] {std::stof(v1[0]), std::stof(v2[0]), std::stof(v3[0])};
					int texIndices[] {std::stof(v1[1]), std::stof(v2[1]), std::stof(v3[1])};
					int normIndices[] {std::stof(v1[2]), std::stof(v2[2]), std::stof(v3[2])};

					faces.push_back(Face(vertIndices, texIndices, normIndices));
				}
			}

			else if(Utility::stringStartsWith(line, "a ")) {
				std::vector<std::string> split;
				Utility::stringSplit(line, ' ', split);
				skeleton = new Skeleton(split[1], modelFile);
			}
		}

		modelFile.close();
	} else {
		std::cout << "Unable to read " << modelName << ".bar" << '\n';
	}


	std::vector<GLfloat> vertBuff;
	std::vector<GLfloat> normBuff;
	std::vector<GLfloat> texCoordBuff;
	std::vector<GLfloat> weightBuff;
	std::vector<GLfloat> weightIndexBuff;

	for(auto& face : faces) {

		vertices[face.vertexIndices[0] - 1].pushOn(&vertBuff);
		vertices[face.vertexIndices[1] - 1].pushOn(&vertBuff);
		vertices[face.vertexIndices[2] - 1].pushOn(&vertBuff);

		if(skeleton != NULL) {
			weights[face.vertexIndices[0] - 1].pushOn(&weightBuff);
			weights[face.vertexIndices[1] - 1].pushOn(&weightBuff);
			weights[face.vertexIndices[2] - 1].pushOn(&weightBuff);

			weightIndices[face.vertexIndices[0] - 1].pushOn(&weightIndexBuff);
			weightIndices[face.vertexIndices[1] - 1].pushOn(&weightIndexBuff);
			weightIndices[face.vertexIndices[2] - 1].pushOn(&weightIndexBuff);
		}

		if(face.hasNormals()) {
			normals[face.normalIndices[0] - 1].pushOn(&normBuff);
			normals[face.normalIndices[1] - 1].pushOn(&normBuff);
			normals[face.normalIndices[2] - 1].pushOn(&normBuff);
		}

		if(face.hasTexCoords()) {
			texCoords[face.texCoordIndices[0] - 1].pushOn(&texCoordBuff);
			texCoords[face.texCoordIndices[1] - 1].pushOn(&texCoordBuff);
			texCoords[face.texCoordIndices[2] - 1].pushOn(&texCoordBuff);
		}
	}

	GLuint verticesVBO, normalsVBO, texCoordVBO, weightVBO, weightIndexVBO;

	GLuint buffs[2];
		
	glGenBuffers(1, buffs);
	verticesVBO = buffs[0];

	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, vertBuff.size() * sizeof(GLfloat), &(vertBuff[0]), GL_STATIC_DRAW);

	if(normals.size() > 0) {
		glGenBuffers(1, buffs);
		normalsVBO = buffs[0];

		glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
		glBufferData(GL_ARRAY_BUFFER, normBuff.size() * sizeof(GLfloat), &(normBuff[0]), GL_STATIC_DRAW);
	}

	if(texCoords.size() > 0) {
		glGenBuffers(1, buffs);
		texCoordVBO = buffs[0];

		glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
		glBufferData(GL_ARRAY_BUFFER, texCoordBuff.size() * sizeof(GLfloat), &(texCoordBuff[0]), GL_STATIC_DRAW);
	}

	if(skeleton != NULL) {
		glGenBuffers(2, buffs);
		weightVBO = buffs[0];
		weightIndexVBO = buffs[1];

		glBindBuffer(GL_ARRAY_BUFFER, weightVBO);
		glBufferData(GL_ARRAY_BUFFER, weightBuff.size() * sizeof(GLfloat), &(weightBuff[0]), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, weightIndexVBO);
		glBufferData(GL_ARRAY_BUFFER, weightIndexBuff.size() * sizeof(GLfloat), &(weightIndexBuff[0]), GL_STATIC_DRAW);
	}

	int vertCount = faces.size() * 3;

	return ModelData(verticesVBO, normalsVBO, texCoordVBO, weightVBO, weightIndexVBO, vertCount, skeleton);

}

//==============================================================================
// Prints the Compile Status of Shader
//==============================================================================
void ShaderUtil::printShaderStatus(std::string message, GLint handle) {
	GLint status;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
	Utility::printToOutput(message + " Compile: " + ((status == GL_TRUE) ? "true" : "false") + '\n');

	GLint length;
	glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
	if (length > 1) {
		std::string temp(length, ' ');
		const char* log = temp.c_str();
		glGetShaderInfoLog(handle, length, NULL, (GLchar*)log);
		Utility::printToOutput(log);
	}
}

//==============================================================================
// Prints the Link Status of Program
//==============================================================================
void ShaderUtil::printProgramStatus(GLint handle) {
	GLint linked;
	glGetProgramiv(handle, GL_LINK_STATUS, &linked);

	Utility::printToOutput(std::string("Program Link: ") + (linked == GL_TRUE ? "true" : "false") + '\n');
	
	GLint length;
	glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
	if (length > 1) {
		std::string temp(length, ' ');
		const char* log = temp.c_str();
		glGetProgramInfoLog(handle, length, NULL, (GLchar*)log);
		Utility::printToOutput(log);
	}
}