#ifndef WORLDSTATE_H
#define WORLDSTATE_H

class WorldState;

#include <list>
#include <mutex>
#include "Main/Player.h"
#include "Models/Tree.h"
#include "Models/Villager.h"
#include "Settlements/Settlement.h"
#include "Main/Camera.h"
#include "Terrain/Sun.h"

class WorldState {

public:
	Player* player;

	std::list<Settlement>* settlements;

	std::list<Tree>* trees;
	
	WorldState();

	void draw(Camera& camera, Sun& sun);
};

#endif