#include "Terrain/Sun.h"
#include "Util/GLMath.h"
#include "Main/Settings.h"
#include <cmath>
#include <string>

Sun::Sun(float theta) 
:
theta(theta * PI_F / 180)
{
	position.x = cos(this->theta);
	position.y = sin(this->theta);
}

void Sun::update(GameTimer& timer) {
	theta += (float)timer.getDelta() * PI_F / SUN_DAY_TIME;

	if(theta > 2 * PI_F)
		theta -= (2 * PI_F);

	position.x = cos(theta);
	position.y = sin(theta);
}

Vector2f Sun::getPosition() {
	return position;
}

std::string Sun::toString() {

	int hours = (int)(theta * (12.0f / PI_F));

	int minutes = (int)(((theta / PI_F) - (hours / 12.0f)) * 720);

	return std::to_string(hours) + ":" + std::to_string(minutes) + " " + std::to_string(theta) + " " + position.toString();
}