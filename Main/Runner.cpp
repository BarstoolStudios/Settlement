/******************************************************************************\
* File: Runner.cpp
*
* Author: Josh Taylor
*
* Header: Runner.h
*
* Description: Entry point for game. Initializes game and starts game loop
\******************************************************************************/

#include "Main/App.h"

int main(int argc, char *argv[]) {
	App app;

	app.gameLoop();

	return 0;
}