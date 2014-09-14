#ifndef BOXCOORD_H
#define BOXCOORD_H

#include <ostream>

class BoxCoord {
public:
	int x, y;

	BoxCoord();
	BoxCoord(int x, int y);

};

bool operator == (const BoxCoord&, const BoxCoord&);

std::ostream& operator << (std::ostream& strm, const BoxCoord& coord);

#endif