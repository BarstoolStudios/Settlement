#ifndef SETTLEMENT_H
#define SETTLEMENT_H

class Settlement;

#include <list>
#include <cstdlib>
#include "Models/Villager.h"
#include "Util/GLMath.h"
#include "Models/Pole.h"
#include "Main/Camera.h"
#include "Terrain/Sun.h"

class Settlement {

	Vector3f location;

	std::list<Villager> villagers;

	Pole pole;

	float influenceRadius;

public:

	Settlement();
	Settlement(Vector3f location, float influenceRadius);

	void draw(Camera& camera, Sun& sun);

};

#endif // SETTLEMENT_H