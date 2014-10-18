#ifndef VILLAGER_H
#define VILLAGER_H
	
#include "Util/GLMath.h"
#include "Models/Skeleton.h"
#include <vector>

class Villager {

	static const float WALK_SPEED;
	static const float FLEE_SPEED;
	static const float ROTATION_SPEED;

	static GLuint VAO;

	static GLint sPositionHandle, sNormalHandle, sSunHandle, sMVPHandle, sNormalMatrixHandle,
		sBoneMatricesHandle, sBoneWeightsHandle, sBoneIndicesHandle;

	static GLuint shaderProgram;

	static GLuint verticesVBO, normalsVBO, boneWeightsVBO, boneIndicesVBO;

	static int vertCount;

	static Skeleton* baseSkeleton;

	Vector3f position;
	GLfloat rotation;

	Skeleton* skeleton;

public:

	Villager(Vector3f position);
	~Villager();

	static void loadResources();

	void draw(Matrix4f projection, Matrix4f view, Vector3f sunDirection);

	Skeleton* getSkeleton();

};

#endif