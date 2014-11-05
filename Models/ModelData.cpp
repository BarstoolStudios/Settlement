/******************************************************************************\
* File: ModelData.cpp
*
* Author: Josh Taylor
*
* Header: ModelData.h
*
* Description: Stores model data, returned after loading
\******************************************************************************/

#include <vector>
#include <GL/glew.h>
#include "Models/ModelData.h"

//==============================================================================
// Used by Model Loader to Return Data To Caller
//==============================================================================

ModelData::ModelData(GLuint verticesVBO, GLuint normalsVBO, GLuint texCoordVBO, GLuint boneWeightsVBO,
	GLuint boneIndicesVBO, int vertCount, Skeleton* skeleton)
	: 
	verticesVBO(verticesVBO), 
	normalsVBO(normalsVBO),
	texCoordVBO(texCoordVBO),
	boneWeightsVBO(boneWeightsVBO),
	boneIndicesVBO(boneIndicesVBO),
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

GLuint ModelData::getBoneWeightsVBO() {
	return boneWeightsVBO;
}

GLuint ModelData::getBoneIndicesVBO() {
	return boneIndicesVBO;
}

int ModelData::getVertCount() {
	return vertCount;
}

Skeleton* ModelData::getSkeleton() {
	return skeleton;
}