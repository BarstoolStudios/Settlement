#ifndef APP_H
#define APP_H

#include <list>
#include "Display.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Camera.h"
#include "GameTimer.h"
#include "Terrain.h"
#include "Tree.h"

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