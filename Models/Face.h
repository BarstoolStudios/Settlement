#ifndef FACE_H
#define FACE_H

class Face {
public:

	int vertexIndices[3];
	int normalIndices[3];
	int texCoordIndices[3];

	Face(int vertexIndices[3]);
	Face(int vertexIndices[3], int normalIndices[3]);
	Face(int vertexIndices[3], int texCoordIndices[3], int normalIndices[3]);
};

#endif