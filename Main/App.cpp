#include <GL/glew.h>
#include <iostream>
#include <list>
#include "Main/App.h"
#include "Main/Settings.h"
#include "Util/ShaderUtil.h"
#include "Models/Tree.h"
#include "Util/Text.h"

App::App() {

	display = new Display();
	keyboard = new Keyboard();
	mouse = new Mouse();
	timer = new GameTimer();
	camera = new Camera(Vector2f(128,128));
	terrain = new Terrain();
	trees = new std::list<Tree>();

	mouse->setGrabbed(true);
	loadResources();

	trees->push_back(Tree(Vector3f(0, terrain->getHeightAt(0, -10), -10)));
}

App::~App() {
	delete display;
	delete keyboard;
	delete mouse;
	delete timer;
	delete camera;
	delete terrain;
	delete trees;
}

void App::loadResources() {
	Tree::loadResources();
	Text::loadResources();
}

void App::input() {

	camera->input(*keyboard, *mouse);

	//------------------------------------------------------------------------------
	// Debugging Code
	//------------------------------------------------------------------------------
	if(keyboard->isKeyDown(Keyboard::KEY_P))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if(keyboard->isKeyDown(Keyboard::KEY_L))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if(keyboard->isKeyDown(Keyboard::KEY_H))
		std::cout << camera->getPosition();

	if (keyboard->isKeyDown(Keyboard::KEY_M))
		mouse->setGrabbed(false);
	if (keyboard->isKeyDown(Keyboard::KEY_N))
		mouse->setGrabbed(true);
}

void App::update() {

	timer->update();

	mouse->update();

	keyboard->update();

	camera->update(*timer, *terrain);

	terrain->update(camera->getPosition());
}

void App::render() {

	terrain->draw(camera->getProjection(), camera->getView(), Vector3f(1, 1, 1));

	for(auto& tree : *trees) {
		tree.draw(camera->getProjection(), camera->getView(), Vector3f(1, 1, 1));
	}

	Text::draw("Hello World!!", Vector2f(22, 22), 12, camera->getTransform2D());
}

void App::gameLoop() {

	while (!display->isQuitRequested()) {
		ShaderUtil::exitOnGLError("App Initialize");
		update();
		ShaderUtil::exitOnGLError("Update");
		input();
		ShaderUtil::exitOnGLError("Input");
		render();
		ShaderUtil::exitOnGLError("Render");
		display->update();
		ShaderUtil::exitOnGLError("Display Update");
	}

	display->destroy();

}