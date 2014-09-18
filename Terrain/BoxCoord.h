#ifndef BOXCOORD_H
#define BOXCOORD_H

#include <ostream>
#include <string>

class BoxCoord {
public:
	int x, y;

	BoxCoord();
	BoxCoord(int x, int y);

	std::string toString();
};

bool operator == (const BoxCoord&, const BoxCoord&);

std::ostream& operator << (std::ostream& strm, const BoxCoord& coord);

#endif