#include <GL/glew.h>
#include <vector>
#include <future>
#include <iostream>
#include "Terrain/TerrainGenerator.h"
#include "Util/TerrainUtil.h"
#include "Util/Utility.h"
#include "Main/Settings.h"

//==============================================================================
// Initialize Static Variables
//==============================================================================
Vector2f TerrainGenerator::fountainLocation = Vector2f(0, 0);
float TerrainGenerator::fountainHeight = 0.0f;
int TerrainGenerator::fountainRadius = -1;

//==============================================================================
// Sets Static Variables When Fountain Is Placed
//==============================================================================
void TerrainGenerator::setFountain(Vector2f location, float height, int radius) {
	fountainLocation = location;
	fountainHeight = height;
	fountainRadius = radius;
}

//==============================================================================
// Constructor
//==============================================================================
TerrainGenerator::TerrainGenerator(int x, int y, std::vector<TerrainSquare>& squaresToBuffer, std::mutex& generatorMutex) {
	X = x;
	Y = y;
	
	this->squaresToBuffer = &squaresToBuffer;
	this->generatorMutex = &generatorMutex;

	if (fountainRadius != -1) {

		BoxCoord upper = getSquare(fountainLocation.x + fountainRadius, fountainLocation.y + fountainRadius);
		BoxCoord lower = getSquare(fountainLocation.x - fountainRadius, fountainLocation.y - fountainRadius);

		if (x >= lower.x && x <= upper.x && y >= lower.y && y <= upper.y)
			shouldAdjust = true;
		else
			shouldAdjust = false;

	}else {
		shouldAdjust = false;
	}
}

//==============================================================================
// Run Function Called By Thread
//==============================================================================
void TerrainGenerator::run(int X, int Y, bool shouldAdjust, std::mutex* generatorMutex, std::vector<TerrainSquare>* squaresToBuffer) {

	float yVals[TERRAIN_SQUARE_SIZE + 1][TERRAIN_SQUARE_SIZE + 1];

	Vector2f topLeftCorner(X * TERRAIN_SQUARE_SIZE, Y * TERRAIN_SQUARE_SIZE);

	int nx, ny;
	if (!shouldAdjust) {
		for (int i = 0; i <= TERRAIN_SQUARE_SIZE; i++) {
			for (int j = 0; j <= TERRAIN_SQUARE_SIZE; j++) {

				nx = topLeftCorner.x + i;
				ny = topLeftCorner.y + j;

				yVals[i][j] = TerrainUtil::octivate(TERRAIN_NUM_OCTIVES, TERRAIN_INITIAL_FREQUENCY, nx, ny) * (float) TERRAIN_HEIGHT;
			}
		}
	}
	else {
		for (int i = 0; i <= TERRAIN_SQUARE_SIZE; i++) {
			for (int j = 0; j <= TERRAIN_SQUARE_SIZE; j++) {

				nx = topLeftCorner.x + i;
				ny = topLeftCorner.y + j;

				if (Utility::distThreshold(fountainLocation.x, fountainLocation.y, nx, ny, (float) fountainRadius))
					yVals[i][j] = fountainHeight;
				else
					yVals[i][j] = TerrainUtil::octivate(TERRAIN_NUM_OCTIVES, TERRAIN_INITIAL_FREQUENCY, nx, ny) * (float)TERRAIN_HEIGHT;
			}
		}
	}

	Vector3f p1, p2, p3, p4, n1, n2;

	std::vector<GLfloat>* vertices = new std::vector<GLfloat>();
	std::vector<GLfloat>* normals = new std::vector<GLfloat>();
	for (int i = 0; i < TERRAIN_SQUARE_SIZE; i++) {
		for (int j = 0; j < TERRAIN_SQUARE_SIZE; j++) {

			p1 = Vector3f(topLeftCorner.x + i,		yVals[i    ][j    ], topLeftCorner.y + j);
			p2 = Vector3f(topLeftCorner.x + i,		yVals[i    ][j + 1], topLeftCorner.y + j + 1);
			p3 = Vector3f(topLeftCorner.x + i + 1,	yVals[i + 1][j + 1], topLeftCorner.y + j + 1);
			p4 = Vector3f(topLeftCorner.x + i + 1,	yVals[i + 1][j    ], topLeftCorner.y + j);

			n1 = Vector3f::norm(Vector3f::cross(p2 - p1, p3 - p1));
			n2 = Vector3f::norm(Vector3f::cross(p3 - p1, p4 - p1));

			p1.pushOn(vertices);
			n1.pushOn(normals);

			p2.pushOn(vertices);
			n1.pushOn(normals);

			p3.pushOn(vertices);
			n1.pushOn(normals);


			p1.pushOn(vertices);
			n2.pushOn(normals);

			p3.pushOn(vertices);
			n2.pushOn(normals);

			p4.pushOn(vertices);
			n2.pushOn(normals);
		}
	}
	generatorMutex->lock();
	TerrainSquare square(X, Y, vertices, normals);
	squaresToBuffer->push_back(square);
	generatorMutex->unlock();
}

//==============================================================================
// Starts New Thread
//==============================================================================
std::future<void>* TerrainGenerator::start() {
	return new std::future<void>(std::async(std::launch::async, TerrainGenerator::run, X, Y, shouldAdjust, generatorMutex, squaresToBuffer));
}

//==============================================================================
// Returns the Grid Coordinate of Top Left Corner of Square that Contains (x, y)
//==============================================================================
BoxCoord TerrainGenerator::getSquare(float x, float z) {
	int nx, nz;

	if (x >= 0)
		nx = (int)x / TERRAIN_SQUARE_SIZE;
	else
		nx = ((int)x / TERRAIN_SQUARE_SIZE) - 1;

	if (z >= 0)
		nz = (int)z / TERRAIN_SQUARE_SIZE;
	else
		nz = ((int)z / TERRAIN_SQUARE_SIZE) - 1;

	return BoxCoord(nx, nz);
}