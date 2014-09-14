#ifndef TERRAINGENERATOR_H
#define TERRAINGENERATOR_H

#include <vector>
#include <future>
#include <mutex>
#include "GLMath.h"
#include "TerrainSquare.h"
#include "BoxCoord.h"

class TerrainGenerator {
	static Vector2f fountainLocation;
	static float fountainHeight;
	static int fountainRadius;

	int X, Y;

	std::vector<TerrainSquare>* squaresToBuffer;

	std::mutex* generatorMutex;

	bool shouldAdjust;

public:

	static void setFountain(Vector2f location, float height, int radius);

	TerrainGenerator(int x, int y, std::vector<TerrainSquare>& squaresToBuffer, std::mutex& generatorMutex);

	static void run(int X, int Y, bool shouldAdjust, std::mutex* generatorMutex, std::vector<TerrainSquare>* squaresToBuffer);

	std::future<void>* start();

	BoxCoord getSquare(float x, float z);
};

#endif