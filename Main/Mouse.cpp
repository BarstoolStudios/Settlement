#include <GL/SDL.h>
#include <iostream>
#include "Main/Mouse.h"
#include "Main/Settings.h"

//==============================================================================
// Constructs Mouse
//==============================================================================
Mouse::Mouse() {
	dx = dy = 0;
	grabbed = false;
	SDL_WarpMouseInWindow(SDL_GL_GetCurrentWindow(), DISPLAY_INITIAL_WIDTH / 2, DISPLAY_INITIAL_HEIGHT / 2);
}

//==============================================================================
// Update Mouse
//==============================================================================
void Mouse::update() {
	if (grabbed)
		SDL_GetRelativeMouseState(&dx, &dy);
}

//==============================================================================
// Sets the Mouse's Grabbed State
//==============================================================================
void Mouse::setGrabbed(bool g) {
	grabbed = g;
	SDL_SetRelativeMouseMode(g ? SDL_TRUE : SDL_FALSE);
	if (!g) {
		dx = 0;
		dy = 0;
	}
}

//==============================================================================
// Get Delta X
//==============================================================================
int Mouse::getDX() {
	return dx;
}

//==============================================================================
// Get Delta Y
//==============================================================================
int Mouse::getDY() {
	return dy;
}

//==============================================================================
// Returns Whether Mouse is Grabbed
//==============================================================================
bool Mouse::isGrabbed() {
	return grabbed;
}