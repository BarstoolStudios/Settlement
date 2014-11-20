/******************************************************************************\
* File: App.cpp
*
* Author: Josh Taylor
*
* Header: App.h
*
* Description: Conatins major functions for game and game loop
\******************************************************************************/

#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include <list>
#include "Main/App.h"
#include "Main/Settings.h"
#include "Util/Utility.h"
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
	camera = new Camera();
	sun = new Sun(0);

	worldState = new WorldState();

	//------------------------------------------------------------------------------
	// Load Static Resources
	//------------------------------------------------------------------------------
	loadResources();

	//------------------------------------------------------------------------------
	// Grabs Mouse
	//------------------------------------------------------------------------------
	mouse->setGrabbed(true);

	worldState->addTree(Vector2f(0, -10));

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
	delete sun;
	delete worldState;
}
//==============================================================================
// Load Static Resources
//==============================================================================
void App::loadResources() {
	
	double t = GameTimer::getTime();
	Villager::loadResources();
	t = GameTimer::getTime() - t;
	std::cout << "Villager: " << t << " ms" << std::endl;


	t = GameTimer::getTime();
	Tree::loadResources();
	t = GameTimer::getTime() - t;
	std::cout << "Tree: " << t << " ms" << std::endl;

	t = GameTimer::getTime();
	Pole::loadResources();
	t = GameTimer::getTime() - t;
	std::cout << "Pole: " << t << " ms" << std::endl;

	t = GameTimer::getTime();
	Text::loadResources();
	t = GameTimer::getTime() - t;
	std::cout << "Text: " << t << " ms" << std::endl;
}

//==============================================================================
// Handle User Input
//==============================================================================
void App::input() {

	worldState->player->input(*keyboard, *mouse, *timer);

	if(keyboard->wasKeyPressed(Keyboard::KEY_H))
		worldState->addPlayerSettlement(32);

	//------------------------------------------------------------------------------
	// Debugging Code
	//------------------------------------------------------------------------------
	if(keyboard->isKeyDown(Keyboard::KEY_P))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if(keyboard->isKeyDown(Keyboard::KEY_L))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (keyboard->wasKeyPressed(Keyboard::KEY_M))
		mouse->setGrabbed(!mouse->isGrabbed());

	if(keyboard->wasKeyPressed(Keyboard::KEY_F3))
		displayDebug = !displayDebug;

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
	camera->update(*(worldState->player));

	//------------------------------------------------------------------------------
	// Update Sun
	//------------------------------------------------------------------------------
	sun->update(*timer);

	//------------------------------------------------------------------------------
	// Update World State
	//------------------------------------------------------------------------------
	worldState->update(*timer);

}

//==============================================================================
// Render Objects
//==============================================================================
void App::render() {

	worldState->draw(*camera, *sun);

	//------------------------------------------------------------------------------
	// Display Debugging Info
	//------------------------------------------------------------------------------
	if(displayDebug) {

		std::ostringstream debug;

		debug	<< "Position: " << worldState->player->getPosition() << '\n'
				<< "Rotation: " << worldState->player->getRotation() << '\n'
				<< "Day Time: "	<< sun->toString() << '\n';

		Text::draw(debug.str(), Vector2f(22,22), 12, camera->getTransform2D());
	}
}

//==============================================================================
// Main Game Loop
//==============================================================================
void App::gameLoop() {

	Utility::exitOnGLError("App Initialize");

	while (!display->isQuitRequested()) {
		input();
		Utility::exitOnGLError("Input");
		update();
		Utility::exitOnGLError("Update");
		render();
		Utility::exitOnGLError("Render");
		display->update();
		Utility::exitOnGLError("Display Update");
	}

	display->destroy();

}