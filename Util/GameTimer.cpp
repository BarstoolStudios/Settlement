/******************************************************************************\
* File: GameTimer.cpp
*
* Author: Josh Taylor
*
* Header: GameTimer.h
*
* Description: A basic timer using <chrono> for time sensitive events.
\******************************************************************************/

#include <chrono>
#include <cmath>
#include "Util/GameTimer.h"

typedef std::chrono::high_resolution_clock hr_clock;

//==============================================================================
// Constructor
//==============================================================================
GameTimer::GameTimer() {
	lastFrame = getTime();
}

//==============================================================================
// Gets System Time in Milliseconds
//==============================================================================
double GameTimer::getTime() {
	hr_clock::time_point time = hr_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>
							(time.time_since_epoch()).count();
}

//==============================================================================
// Returns delta
//==============================================================================
double GameTimer::getDelta() {
	return delta;
}

//==============================================================================
// Returns fps
//==============================================================================
int GameTimer::getFPS() {
	return fps;
}

//==============================================================================
// Updates delta and fps
//==============================================================================
void GameTimer::update() {
	double currentTime = getTime();
	delta = currentTime - lastFrame;
	fps = (int)round(1000/delta);
	lastFrame = getTime();
}