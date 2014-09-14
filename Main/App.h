#ifndef APP_H
#define APP_H

#include <list>
#include "Main/Display.h"
#include "Main/Keyboard.h"
#include "Main/Mouse.h"
#include "Main/Camera.h"
#include "Util/GameTimer.h"
#include "Terrain/Terrain.h"
#include "Models/Tree.h"

class App {
	Display* display;
	Keyboard* keyboard;
	Mouse* mouse;
	GameTimer* timer;
	Camera* camera;
	Terrain* terrain;
	std::list<Tree>* trees;

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