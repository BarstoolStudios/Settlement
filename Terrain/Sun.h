#ifndef SUN_H
#define SUN_H

class Sun;

#include "Util/GLMAth.h"
#include "Util/GameTimer.h"
#include <string>

class Sun {

	float theta;

	Vector2f position;

public:

	Sun(float theta);

	void update(GameTimer& timer);

	Vector2f getPosition();

	std::string toString();
};

#endif // SUN_H