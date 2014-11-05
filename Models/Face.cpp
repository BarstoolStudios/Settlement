/******************************************************************************\
* File: Face.cpp
*
* Author: Josh Taylor
*
* Header: Face.h
*
* Description: Used when loading models to store face data
\******************************************************************************/

#include "Models/Face.h"
#include <iostream>

Face::Face(int vertexIndices[3]) {
	this->vertexIndices[0] = vertexIndices[0];
	this->vertexIndices[1] = vertexIndices[1];
	this->vertexIndices[2] = vertexIndices[2];

	this->normalIndices[0] = 0;
	this->normalIndices[1] = 0;
	this->normalIndices[2] = 0;

	this->texCoordIndices[0] = 0;
	this->texCoordIndices[1] = 0;
	this->texCoordIndices[2] = 0;
}

Face::Face(int vertexIndices[3], int normalIndices[3]) : Face(vertexIndices) {
	this->normalIndices[0] = normalIndices[0];
	this->normalIndices[1] = normalIndices[1];
	this->normalIndices[2] = normalIndices[2];
}

Face::Face(int vertexIndices[3], int texCoordIndices[3], int normalIndices[3]) : Face(vertexIndices, normalIndices) {
	this->texCoordIndices[0] = texCoordIndices[0];
	this->texCoordIndices[1] = texCoordIndices[1];
	this->texCoordIndices[2] = texCoordIndices[2];
}

bool Face::hasNormals() {
	return (normalIndices[0] != 0);
}

bool Face::hasTexCoords() {
	return (texCoordIndices[0] != 0);
}