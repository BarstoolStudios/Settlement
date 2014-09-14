#include <vector>
#include <GL\glew.h>
#include "ModelData.h"

ModelData::ModelData(GLuint verticesVBO, GLuint normalsVBO, GLuint texCoordVBO, GLuint skeletonWeightsVBO,
	GLuint skeletonWeightIndicesVBO, int vertCount, Skeleton* skeleton)
	: 
	verticesVBO(verticesVBO), 
	normalsVBO(normalsVBO),
	texCoordVBO(texCoordVBO),
	skeletonWeightsVBO(skeletonWeightsVBO),
	skeletonWeightIndicesVBO(skeletonWeightIndicesVBO),
	vertCount(vertCount),
	skeleton(skeleton)
	{}

GLuint ModelData::getVerticesVBO() {
	return verticesVBO;
}

GLuint ModelData::getNormalsVBO() {
	return normalsVBO;
}

GLuint ModelData::getTexCoordVBO() {
	return texCoordVBO;
}

GLuint ModelData::getSkeletonWeightsVBO() {
	return skeletonWeightsVBO;
}

GLuint ModelData::getSkeletonWeightIndices() {
	return skeletonWeightIndicesVBO;
}

int ModelData::getVertCount() {
	return vertCount;
}

Skeleton* ModelData::getSkeleton() {
	return skeleton;
}