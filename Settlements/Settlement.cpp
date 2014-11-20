#include "Settlements/Settlement.h"
#include <cstdlib>

Settlement::Settlement() : Settlement(Circle(), 0) {}
Settlement::Settlement(Circle area, float height)
:
	area(area),
	height(height),
	pole(Vector3f(area.center.x, height, area.center.y), Vector3f(rand(), rand(), rand()) / RAND_MAX)
{}

void Settlement::draw(Camera& camera, Sun& sun) {

	pole.draw(camera, sun);

}

Circle Settlement::getArea() {
	return area;
}

float Settlement::getHeight() {
	return height;
}