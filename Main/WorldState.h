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
	
	Terrain* terrain;
	
	WorldState();
	~WorldState();

	void draw(Camera& camera, Sun& sun);

	void update(GameTimer& timer);

	void addPlayerSettlement(float radius);

	void addTree(Vector2f pos);
};

#endif // WORLDSTATE_H