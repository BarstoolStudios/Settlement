#ifndef TREE_H
#define TREE_H

#include "GLMath.h"

class Tree {

	Vector3f position;

	static GLuint VAO;

	static GLint sPositionHandle, sNormalHandle, sSunHandle, sMVPHandle, sNormalMatrixHandle;

	static GLuint shaderProgram;

	static GLuint verticesVBO, normalsVBO;

	static int vertCount;

public:
	Tree(Vector3f position);

	static void loadResources();

	void draw(Matrix4f projection, Matrix4f view, Vector3f sunDirection);
};

#endif