/******************************************************************************\
* File: TerrainSquare.cpp
*
* Author: Josh Taylor
*
* Header: TerrainSquare.h
*
* Description: Created by TerrainGenerator and stores Terrain data
\******************************************************************************/

#include <GL/glew.h>
#include <vector>
#include <climits>
#include <string>
#include "Terrain/TerrainSquare.h"
#include "Util/GLMath.h"

//==============================================================================
// Stores Data For Squares
//==============================================================================

TerrainSquare::TerrainSquare() 
:
coord(INT_MAX, INT_MAX)
{}

TerrainSquare::TerrainSquare(Vector2i coord, std::vector<GLfloat>* vertices, std::vector<GLfloat>* normals) 
:
	coord(coord),
	vertices(vertices),
	normals(normals)
{}

bool TerrainSquare::operator == (const TerrainSquare& other) {
	return coord == other.coord;
}
bool TerrainSquare::operator != (const TerrainSquare& other) {
	return coord != other.coord;
}

std::string TerrainSquare::toString() {
	return std::string("[") + std::to_string(coord.x) + ", " + std::to_string(coord.y) + "]";
}

std::ostream& operator << (std::ostream &strm, TerrainSquare& sqr) {
	return strm << sqr.toString();
}