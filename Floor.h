#ifndef FLOOR_H
#define FLOOR_H

#include <string>
#include <vector>
#include "GLMath.h"

class Floor {
	static std::string vertexShaderCode;
	static std::string fragmentShaderCode;

	static GLuint shaderProgram;

	static GLuint VAO;

	static GLuint vboVertexHandle;

	static GLint sPositionHandle, sColorHandle, sMVPHandle;

	static std::vector<GLfloat> vertices;

	Vector3f color;

public:
	Floor();

	static void loadResources();

	void draw(Matrix4f projection, Matrix4f view);

};

#endif