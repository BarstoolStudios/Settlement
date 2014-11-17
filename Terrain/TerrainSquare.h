#ifndef TERRAINSQUARE_H
#define TERRAINSQUARE_H

class TerrainSquare;

#include <GL/glew.h>
#include <ostream>
#include <vector>
#include <string>
#include "Util/GLMath.h"

class TerrainSquare {
public:
	Vector2i coord;
	std::vector<GLfloat>* vertices;
	std::vector<GLfloat>* normals;

	TerrainSquare();
	TerrainSquare(Vector2i coord, std::vector<GLfloat>* vertices, std::vector<GLfloat>* normals);

	std::string toString();

	bool operator == (const TerrainSquare&);
	bool operator != (const TerrainSquare&);
};

std::ostream& operator << (std::ostream &strm, const TerrainSquare& sqr);

#endif