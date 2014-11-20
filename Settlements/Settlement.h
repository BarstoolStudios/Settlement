#ifndef SETTLEMENT_H
#define SETTLEMENT_H

class Settlement;

#include <list>
#include <cstdlib>
#include "Models/Villager.h"
#include "Util/GLMath.h"
#include "Main/Camera.h"
#include "Terrain/Sun.h"
#include "Util/GLMath.h"
#include "Models/Pole.h"

class Settlement {

	Circle area;
	float height;

	std::list<Villager> villagers;

	Pole pole;

public:

	Settlement();
	Settlement(Circle area, float height);

	void draw(Camera& camera, Sun& sun);

	Circle getArea();
	float getHeight();
};

#endif // SETTLEMENT_H