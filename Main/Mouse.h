#ifndef MOUSE_H
#define MOUSE_H
	
#include "GLMath.h"
class Mouse {
	int dx, dy;

	bool grabbed;

public:
	Mouse();

	void update();

	void setGrabbed(bool g);

	int getDX();

	int getDY();

	int getX();

	int getY();

	bool isGrabbed();
};

#endif