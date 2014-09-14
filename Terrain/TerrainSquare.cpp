#include <GL\glew.h>
#include <vector>
#include <climits>
#include <string>
#include "TerrainSquare.h"

TerrainSquare::TerrainSquare() {
	x = INT_MAX;
	y = INT_MAX;
}

TerrainSquare::TerrainSquare(int x, int y, std::vector<GLfloat>* vertices, std::vector<GLfloat>* normals) {
	this->x = x;
	this->y = y;
	this->vertices = vertices;
	this->normals = normals;
}

bool TerrainSquare::operator == (const TerrainSquare& other) {
	return x == other.x && y == other.y;
}
bool TerrainSquare::operator != (const TerrainSquare& other) {
	return x != other.x || y != other.y;
}

std::string TerrainSquare::toString() {
	return std::string("[") + std::to_string(x) + ", " + std::to_string(y) + "]";
}

std::ostream& operator << (std::ostream &strm, TerrainSquare& sqr) {
	return strm << sqr.toString();
}