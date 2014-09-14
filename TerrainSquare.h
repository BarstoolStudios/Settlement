#ifndef TERRAINSQUARE_H
#define TERRAINSQUARE_H

#include <GL\glew.h>
#include <ostream>
#include <vector>
#include <string>


class TerrainSquare {
public:
	int x, y;
	std::vector<GLfloat>* vertices;
	std::vector<GLfloat>* normals;

	TerrainSquare();
	TerrainSquare(int x, int y, std::vector<GLfloat>* vertices, std::vector<GLfloat>* normals);

	std::string toString();

	bool operator == (const TerrainSquare&);
	bool operator != (const TerrainSquare&);
};

std::ostream& operator << (std::ostream &strm, const TerrainSquare& sqr);

#endif