#include <GL/SDL.h>
#include <iostream>
#include "Main/Keyboard.h"

Keyboard::Keyboard() {
	keys = SDL_GetKeyboardState(NULL);

	for(int i = 0; i < KEY_MAX; i++)
		prev[i] = keys[i];

}

void Keyboard::update() {
	for(int i = 0; i < KEY_MAX; i++)
		prev[i] = keys[i];

	SDL_PumpEvents();
}

bool Keyboard::isKeyDown(int key) {
	return (bool) keys[key];
}

bool Keyboard::wasKeyPressed(int key) {
	return keys[key] && ! prev[key];
}

bool Keyboard::wasKeyReleased(int key) {
	return !keys[key] && prev[key];
}