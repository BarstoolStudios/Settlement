#ifndef MODELDATA_H
#define MODELDATA_H

class ModelData;

#include <vector>
#include <GL/glew.h>
#include "Models/Skeleton.h"

class ModelData {
	GLuint verticesVBO, normalsVBO, texCoordVBO, boneWeightsVBO, boneIndicesVBO;

	int vertCount;

	Skeleton* skeleton;

public:
	ModelData(GLuint verticesVBO, GLuint normalsVBO, GLuint texCoordVBO, GLuint boneWeightsVBO,
		GLuint boneIndicesVBO, int vertCount, Skeleton* skeleton);

	GLuint getVerticesVBO();

	GLuint getNormalsVBO();

	GLuint getTexCoordVBO();

	GLuint getBoneWeightsVBO();

	GLuint getBoneIndicesVBO();

	int getVertCount();

	Skeleton* getSkeleton();
};

#endif