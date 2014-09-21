#include "Terrain/BoxCoord.h"
#include <ostream>
#include <string>
#include <climits>

//==============================================================================
// Used by Terrain to Store Square Coordinates
//==============================================================================

BoxCoord::BoxCoord() {
	x = INT_MAX;
	y = INT_MAX;
}

BoxCoord::BoxCoord(int x, int y) {
	this->x = x;
	this->y = y;
}

std::string BoxCoord::toString() {
	return std::string("(") + std::to_string(x) + ", " + std::to_string(y) + ")";
}

bool operator == (const BoxCoord& b1, const BoxCoord& b2) {
	return b1.x == b2.x && b1.y == b2.y;
}

std::ostream& operator << (std::ostream& strm, const BoxCoord& coord) {
	return strm << '[' << coord.x << ", " << coord.y << "]\n";
}