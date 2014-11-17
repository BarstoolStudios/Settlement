/******************************************************************************\
* File: Keyboard.cpp
*
* Author: Josh Taylor
*
* Header: Keyboard.h
*
* Description: Provides wrapper and added functionality for SDL keyboard
\******************************************************************************/

#include <GL/SDL.h>
#include <iostream>
#include "Main/Keyboard.h"

//==============================================================================
// Construct Keyboard
//==============================================================================
Keyboard::Keyboard() {
	keys = SDL_GetKeyboardState(NULL);

	for(int i = 0; i < KEY_MAX; i++)
		prev[i] = keys[i];

}

//==============================================================================
// Update Keyboard
//==============================================================================
void Keyboard::update() {
	for(int i = 0; i < KEY_MAX; i++)
		prev[i] = keys[i];

	SDL_PumpEvents();
}

//==============================================================================
// Returns Whether Key is Down
//==============================================================================
bool Keyboard::isKeyDown(int key) {
	return (bool)keys[key];
}

//==============================================================================
// Returns True the Iteration that Key was Pressed
//==============================================================================
bool Keyboard::wasKeyPressed(int key) {
	return keys[key] && ! prev[key];
}

//==============================================================================
// Returns True the Iteration that Key was Released
//==============================================================================
bool Keyboard::wasKeyReleased(int key) {
	return !keys[key] && prev[key];
}