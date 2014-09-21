#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include <list>
#include "Main/App.h"
#include "Main/Settings.h"
#include "Util/ShaderUtil.h"
#include "Models/Tree.h"
#include "Util/Text.h"

//==============================================================================
// Constructor
//==============================================================================
App::App() {

	//------------------------------------------------------------------------------
	// Create App Members
	//------------------------------------------------------------------------------
	display = new Display();
	keyboard = new Keyboard();
	mouse = new Mouse();
	timer = new GameTimer();
	camera = new Camera(Vector2f(128,128));
	terrain = new Terrain();
	trees = new std::list<Tree>();

	//------------------------------------------------------------------------------
	// Grabs Mouse
	//------------------------------------------------------------------------------
	mouse->setGrabbed(true);

	//------------------------------------------------------------------------------
	// Load Static Resources
	//------------------------------------------------------------------------------
	loadResources();

	//------------------------------------------------------------------------------
	// Adds a tree (Testing Code)
	//------------------------------------------------------------------------------
	trees->push_back(Tree(Vector3f(0, terrain->getHeightAt(0, -10), -10)));
}

//==============================================================================
// Deconstructor
//==============================================================================
App::~App() {
	delete display;
	delete keyboard;
	delete mouse;
	delete timer;
	delete camera;
	delete terrain;
	delete trees;
}
//==============================================================================
// Load Static Resources
//==============================================================================
void App::loadResources() {

	Tree::loadResources();
	
	Text::loadResources();
}

//==============================================================================
// Handle User Input
//==============================================================================
void App::input() {

	//------------------------------------------------------------------------------
	// Camera Input
	//------------------------------------------------------------------------------
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

	if(keyboard->wasKeyPressed(Keyboard::KEY_F3)) {
		displayDebug = !displayDebug;
	}
}

//==============================================================================
// Update Game Objects
//==============================================================================
void App::update() {

	//------------------------------------------------------------------------------
	// Update Timer
	//------------------------------------------------------------------------------
	timer->update();

	//------------------------------------------------------------------------------
	// Update Mouse
	//------------------------------------------------------------------------------
	mouse->update();

	//------------------------------------------------------------------------------
	// Update Keyboard
	//------------------------------------------------------------------------------
	keyboard->update();

	//------------------------------------------------------------------------------
	// Update Camera
	//------------------------------------------------------------------------------
	camera->update(*timer, *terrain);

	//------------------------------------------------------------------------------
	// Update Terrain
	//------------------------------------------------------------------------------
	terrain->update(camera->getPosition());
}

//==============================================================================
// Render Objects
//==============================================================================
void App::render() {

	//------------------------------------------------------------------------------
	// Draw Terrain
	//------------------------------------------------------------------------------
	terrain->draw(camera->getProjection(), camera->getView(), Vector3f(1, 1, 1));

	//------------------------------------------------------------------------------
	// Draw Trees
	//------------------------------------------------------------------------------
	for(auto& tree : *trees) {
		tree.draw(camera->getProjection(), camera->getView(), Vector3f(1, 1, 1));
	}


	//------------------------------------------------------------------------------
	// Display Debugging Info
	//------------------------------------------------------------------------------
	if(displayDebug) {

		std::ostringstream debug;

		debug	<< "Position: " << camera->getPosition() << '\n'
				<< "Rotation: " << camera->getRotation() << '\n'
				<< "Current Square: " << terrain->getSquareCoord(camera->getPosition().x, camera->getPosition().z).toString() << '\n';

		Text::draw(debug.str(), Vector2f(22,22), 12, camera->getTransform2D());
	}
}

//==============================================================================
// Main Game Loop
//==============================================================================
void App::gameLoop() {

	ShaderUtil::exitOnGLError("App Initialize");

	while (!display->isQuitRequested()) {
		input();
		ShaderUtil::exitOnGLError("Input");
		update();
		ShaderUtil::exitOnGLError("Update");
		render();
		ShaderUtil::exitOnGLError("Render");
		display->update();
		ShaderUtil::exitOnGLError("Display Update");
	}

	display->destroy();

}