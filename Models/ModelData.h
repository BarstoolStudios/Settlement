#ifndef MODELDATA_H
#define MODELDATA_H

#include <vector>
#include <GL\glew.h>
#include "Skeleton.h"

class ModelData {
	GLuint verticesVBO, normalsVBO, texCoordVBO, skeletonWeightsVBO, skeletonWeightIndicesVBO;

	int vertCount;

	Skeleton* skeleton;

public:
	ModelData(GLuint verticesVBO, GLuint normalsVBO, GLuint texCoordVBO, GLuint skeletonWeightsVBO,
		GLuint skeletonWeightIndicesVBO, int vertCount, Skeleton* skeleton);

	GLuint getVerticesVBO();

	GLuint getNormalsVBO();

	GLuint getTexCoordVBO();

	GLuint getSkeletonWeightsVBO();

	GLuint getSkeletonWeightIndices();

	int getVertCount();

	Skeleton* getSkeleton();
};

#endif