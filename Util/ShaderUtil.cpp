#include <GL\glew.h>
#include "ShaderUtil.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <SOIL.h>
#include "GLMath.h"
#include "Face.h"
#include "Utility.h"

GLint ShaderUtil::loadShader(GLenum type, std::string shaderCode) {
	GLint shader = glCreateShader(type);

	const char* str = shaderCode.c_str();

	glShaderSource(shader, 1, &str, NULL);

	glCompileShader(shader);

	return shader;
}

std::string ShaderUtil::readShaderFromFile(std::string shaderName) {
	std::string text = "";
	std::string line = "";

	std::ifstream shaderFile(shaderName);

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

GLint ShaderUtil::createProgram(std::string modelName, std::vector<GLenum> shaders, bool printStatus) {
	std::string header = std::string(7, '-') + ' ' + modelName + " Shaders " + std::string(7, '-');

	printToOutput(header + '\n');

	GLint shaderProgram = glCreateProgram();

	for (int i = 0; i < shaders.size(); i++) {
		switch (shaders[i]) {
		
		case GL_VERTEX_SHADER: {
			std::string vertCode = ShaderUtil::readShaderFromFile(modelName + ".vert");
			GLint vertexShader = ShaderUtil::loadShader(GL_VERTEX_SHADER, vertCode);
			glAttachShader(shaderProgram, vertexShader);
			if (printStatus)
			ShaderUtil::printShaderStatus("Vertex", vertexShader);
			break;
		}

		case GL_FRAGMENT_SHADER: {
			std::string fragCode = ShaderUtil::readShaderFromFile(modelName + ".frag");
			GLint fragmentShader = ShaderUtil::loadShader(GL_FRAGMENT_SHADER, fragCode);
			glAttachShader(shaderProgram, fragmentShader);
			if (printStatus)
			ShaderUtil::printShaderStatus("Fragment", fragmentShader);
			break;
		}

		case GL_TESS_CONTROL_SHADER: {
			std::string tescCode = ShaderUtil::readShaderFromFile(modelName + ".tesc");
			GLint tessControlShader = ShaderUtil::loadShader(GL_TESS_CONTROL_SHADER, tescCode);
			glAttachShader(shaderProgram, tessControlShader);
			if (printStatus)
			ShaderUtil::printShaderStatus("Tessellation Control", tessControlShader);
			break;
		}

		case GL_TESS_EVALUATION_SHADER: {
			std::string teseCode = ShaderUtil::readShaderFromFile(modelName + ".tese");
			GLint tessEvaluationShader = ShaderUtil::loadShader(GL_TESS_EVALUATION_SHADER, teseCode);
			glAttachShader(shaderProgram, tessEvaluationShader);
			if (printStatus)
				ShaderUtil::printShaderStatus("Tessellation Evaluation", tessEvaluationShader);
			break;
		}

		case GL_GEOMETRY_SHADER: {
			std::string geomCode = ShaderUtil::readShaderFromFile(modelName + ".geom");
			GLint geometryShader = ShaderUtil::loadShader(GL_GEOMETRY_SHADER, geomCode);
			glAttachShader(shaderProgram, geometryShader);
			if (printStatus)
				ShaderUtil::printShaderStatus("Geometry", geometryShader);
			break;
		}
		}
	}

	glLinkProgram(shaderProgram);

	printProgramStatus(shaderProgram);

	printToOutput(std::string(header.size(), '-') + '\n');

	return shaderProgram;
}

GLint ShaderUtil::loadPNG(std::string pngName) {
	
}

ModelData ShaderUtil::loadModel(std::string modelName) {
	std::string line = "";

	std::vector<Vector3f> vertices;
	std::vector<Vector3f> normals;
	std::vector<Vector2f> texCoords;
	std::vector<Vector3f> weights;
	std::vector<Vector3f> weightIndices;
	std::vector<Face> faces;

	std::ifstream modelFile(modelName + ".bar");

	if(modelFile.is_open()) {

		while(std::getline(modelFile, line)) {
			
			// Process vertex position
			if(Utility::stringStartsWith(line, "v ")) {
				std::vector<std::string> split;
				Utility::stringSplit(line, ' ', split);

				vertices.push_back(Vector3f(std::stof(split[1]), std::stof(split[2]), std::stof(split[3])));
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

				int vertIndices[] {std::stof(v1[0]), std::stof(v2[0]), std::stof(v3[0])};
				int texIndices[] {std::stof(v1[1]), std::stof(v2[1]), std::stof(v3[1])};
				int normIndices[] {std::stof(v1[2]), std::stof(v2[2]), std::stof(v3[2])};

				faces.push_back(Face(vertIndices, texIndices, normIndices));
			}
		}

		modelFile.close();
	} else {
		std::cout << "Unable to read " << modelName << ".bar" << '\n';
	}

	std::vector<GLfloat> vertBuff;
	std::vector<GLfloat> normBuff;
	std::vector<GLfloat> texCoordBuff;

	for(auto& face : faces) {
		// Vertex 1
		vertices[face.vertexIndices[0] - 1].pushOn(&vertBuff);
		normals[face.normalIndices[0] - 1].pushOn(&normBuff);
		texCoords[face.texCoordIndices[0] - 1].pushOn(&texCoordBuff);

		// Vertex 2
		vertices[face.vertexIndices[1] - 1].pushOn(&vertBuff);
		normals[face.normalIndices[1] - 1].pushOn(&normBuff);
		texCoords[face.texCoordIndices[1] - 1].pushOn(&texCoordBuff);

		// Vertex 3
		vertices[face.vertexIndices[2] - 1].pushOn(&vertBuff);
		normals[face.normalIndices[2] - 1].pushOn(&normBuff);
		texCoords[face.texCoordIndices[2] - 1].pushOn(&texCoordBuff);
	}

	GLuint buffs[3];
	glGenBuffers(3, buffs);

	int verticesVBO = buffs[0];
	int normalsVBO = buffs[1];
	int texCoordVBO = buffs[2];

	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, vertBuff.size() * sizeof(GLfloat), &(vertBuff[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
	glBufferData(GL_ARRAY_BUFFER, normBuff.size() * sizeof(GLfloat), &(normBuff[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, texCoordBuff.size() * sizeof(GLfloat), &(texCoordBuff[0]), GL_STATIC_DRAW);

	int vertCount = faces.size() * 3;

	return ModelData(verticesVBO, normalsVBO, texCoordVBO, 0, 0, vertCount, NULL);
}

void ShaderUtil::exitOnGLError(std::string errorMessage) {
	GLenum errorValue = glGetError();

	if (errorValue != GL_NO_ERROR) {
		
		switch (errorValue) {
		
		case GL_INVALID_ENUM:
			printToOutput(std::string("OpenGL Error: Invalid Enum -- ") + errorMessage + '\n');
			break;

		case GL_INVALID_VALUE:
			printToOutput(std::string("OpenGL Error: Invalid Value -- ") + errorMessage + '\n');
			break;

		case GL_INVALID_OPERATION:
			printToOutput(std::string("OpenGL Error: Invalid Operation -- ") + errorMessage + '\n');
			break;

		case GL_INVALID_FRAMEBUFFER_OPERATION:
			printToOutput(std::string("OpenGL Error: Invalid Framebuffer Operation -- ") + errorMessage + '\n');
			break;

		case GL_OUT_OF_MEMORY:
			printToOutput(std::string("OpenGL Error: Out of Memory -- ") + errorMessage + '\n');
			break;

		case GL_STACK_UNDERFLOW:
			printToOutput(std::string("OpenGL Error: Stack Underflow -- ") + errorMessage + '\n');
			break;

		case GL_STACK_OVERFLOW:
			printToOutput(std::string("OpenGL Error: Stack Overflow -- ") + errorMessage + '\n');
			break;
		}

		exit(EXIT_FAILURE);
	}
}

void ShaderUtil::printShaderStatus(std::string message, GLint handle) {
	GLint status;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
	printToOutput(message + " Compile: " + ((status == GL_TRUE) ? "true" : "false") + '\n');

	GLint length;
	glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
	if (length > 1) {
		std::string temp(length, ' ');
		const char* log = temp.c_str();
		glGetShaderInfoLog(handle, length, NULL, (GLchar*)log);
		printToOutput(log);
	}
}

void ShaderUtil::printProgramStatus(GLint handle) {
	GLint linked;
	glGetProgramiv(handle, GL_LINK_STATUS, &linked);

	printToOutput(std::string("Program Link: ") + (linked == GL_TRUE ? "true" : "false") + '\n');
	
	GLint length;
	glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
	if (length > 1) {
		std::string temp(length, ' ');
		const char* log = temp.c_str();
		glGetProgramInfoLog(handle, length, NULL, (GLchar*)log);
		printToOutput(log);
	}
}

void ShaderUtil::printToOutput(std::string str) {
	OutputDebugString(str.c_str());
}