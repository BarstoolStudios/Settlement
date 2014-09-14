#ifndef GAMETIMER_H
#define GAMETIMER_H

class GameTimer {
	double lastFrame;
	double delta;

	int fps;

public:
	GameTimer();

	double getTime();
	double getDelta();

	int getFPS();

	void update();
};

#endif