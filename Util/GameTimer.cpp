#include <ctime>
#include <cmath>
#include "GameTimer.h"

GameTimer::GameTimer() {
	lastFrame = getTime();
}

double GameTimer::getTime() {
	return (double) time(0) / 1000000.0f;
}

double GameTimer::getDelta() {
	return delta;
}

int GameTimer::getFPS() {
	return fps;
}

void GameTimer::update() {
	double currentTime = getTime();
	delta = currentTime - lastFrame;
	fps = (int)round(1000/delta);
	lastFrame = getTime();
}