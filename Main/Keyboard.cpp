#include <GL/SDL.h>
#include "Main/Keyboard.h"

Keyboard::Keyboard() {
	keys = SDL_GetKeyboardState(NULL);
}

void Keyboard::update() {
	SDL_PumpEvents();
	keys = SDL_GetKeyboardState(NULL);
}

bool Keyboard::isKeyDown(int key) {
	return (bool) keys[key];
}