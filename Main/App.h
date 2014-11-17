#ifndef APP_H
#define APP_H

class App;

#include <list>
#include "Main/Display.h"
#include "Main/Keyboard.h"
#include "Main/Mouse.h"
#include "Main/Camera.h"
#include "Main/WorldState.h"
#include "Util/GameTimer.h"
#include "Terrain/Sun.h"
#include "Models/Tree.h"
#include "Models/Villager.h"
#include "Terrain/Terrain.h"

class App {
	Display* display;
	Keyboard* keyboard;
	Mouse* mouse;
	GameTimer* timer;
	Camera* camera;
	Terrain* terrain;
	Sun* sun;
	WorldState* worldState;

	bool displayDebug;

	void loadResources();

	void input();

	void update();

	void render();

public:
	App();
	~App();

	void gameLoop();
};

#endif