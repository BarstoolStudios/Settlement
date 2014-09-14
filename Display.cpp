#include <GL\glew.h>
#include <GL\SDL.h>
#include <iostream>
#include "Display.h"
#include "Settings.h"
#include "ShaderUtil.h"

Display::Display() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		ShaderUtil::printToOutput("Could not initialize SDL\n");
		exit(-1);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, OPENGL_DEPTH_BUFFER_SIZE);

	window = SDL_CreateWindow(
		"Settlement",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		DISPLAY_INITIAL_WIDTH,
		DISPLAY_INITIAL_HEIGHT,
		SDL_WINDOW_OPENGL
	);

	if (window == NULL) {
		ShaderUtil::printToOutput("Could not create window\n");
		exit(-1);
	}

	if ((GLcontext = SDL_GL_CreateContext(window)) == NULL) {
		ShaderUtil::printToOutput("Could not create OpenGL context\n");
		exit(-1);
	}

	SDL_GL_SetSwapInterval(1);

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK) {
		ShaderUtil::printToOutput("glew failed to initialize.");
		exit(EXIT_FAILURE);
	}
	glGetError(); // glewInit generates GL_INVALID_ENUM  WTF

	glClearColor(0.0f, 0.746f, 1.0f, 1.0f);
	glClearDepth(1.0f);

	glViewport(0, 0, DISPLAY_INITIAL_WIDTH, DISPLAY_INITIAL_HEIGHT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Display::update() {
	SDL_GL_SwapWindow(window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::destroy() {

	SDL_GL_DeleteContext(GLcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

bool Display::isQuitRequested() {
	return (bool) SDL_QuitRequested();
}