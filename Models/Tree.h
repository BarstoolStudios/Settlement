#ifndef TREE_H
#define TREE_H

class Tree;

#include <GL/glew.h>
#include "Util/GLMath.h"
#include "Main/Camera.h"
#include "Terrain/Sun.h"

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

	void draw(Camera& camera, Sun& sun);
};

#endif // TREE_H