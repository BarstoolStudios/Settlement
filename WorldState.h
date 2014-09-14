#ifndef WORLDSTATE_H
#define WORLDSTATE_H

#include "Camera.h"
#include "GameTimer.h"
#include "Terrain.h"
#include "ModelList.h"

class WorldState {
public:
	Camera camera;

	GameTimer timer;
	
	ModelList models;

	ModelList drops;

	ModelList villagers;

	Terrain terrain;
};

#endif