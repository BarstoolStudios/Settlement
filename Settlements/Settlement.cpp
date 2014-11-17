#include "Settlements/Settlement.h"
#include <cstdlib>

Settlement::Settlement() : Settlement(Vector3f(0, 0, 0), 0) {}
Settlement::Settlement(Vector3f location, float influenceRadius)
:
	location(location),
	pole(location, Vector3f(rand(), rand(), rand()) / RAND_MAX),
	influenceRadius(influenceRadius)
{}

void Settlement::draw(Camera& camera, Sun& sun) {

	pole.draw(camera, sun);

}