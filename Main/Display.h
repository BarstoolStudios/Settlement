#ifndef DISPLAY_H
#define DISPLAY_H

#include <GL\glew.h>
#include <GL\SDL.h>

class Display {
	SDL_Window* window;
	SDL_GLContext GLcontext;

public:
	Display();

	void update();

	void destroy();

	bool isQuitRequested();
};

#endif