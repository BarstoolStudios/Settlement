#ifndef POLE_H
#define POLE_H

class Pole;

#include <GL/glew.h>
#include "Util/GLMath.h"
#include "Main/Camera.h"
#include "Terrain/Sun.h"

class Pole {

	Vector3f position;
	Vector3f color;

	static GLuint VAO;

	static GLint sPositionHandle, sNormalHandle, sSunHandle, sMVPHandle, sNormalMatrixHandle;

	static GLuint shaderProgram;

	static GLuint verticesVBO, normalsVBO;

	static int vertCount;

public:

	Pole(Vector3f position, Vector3f color);

	static void loadResources();

	void draw(Camera& camera, Sun& sun);
};

#endif // POLE_H