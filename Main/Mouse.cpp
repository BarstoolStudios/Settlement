#include <GL/SDL.h>
#include <iostream>
#include "Mouse.h"
#include "Settings.h"

Mouse::Mouse() {
	dx = dy = 0;
	grabbed = false;
	SDL_WarpMouseInWindow(SDL_GL_GetCurrentWindow(), DISPLAY_INITIAL_WIDTH / 2, DISPLAY_INITIAL_HEIGHT / 2);
}

void Mouse::update() {
	if (grabbed)
		SDL_GetRelativeMouseState(&dx, &dy);
}

void Mouse::setGrabbed(bool g) {
	grabbed = g;
	SDL_SetRelativeMouseMode(g ? SDL_TRUE : SDL_FALSE);
	if (!g) {
		dx = 0;
		dy = 0;
	}
}

int Mouse::getDX() {
	return dx;
}

int Mouse::getDY() {
	return dy;
}

bool Mouse::isGrabbed() {
	return grabbed;
}