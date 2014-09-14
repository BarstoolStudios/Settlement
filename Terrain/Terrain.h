#ifndef TERRAIN_H
#define TERRAIN_H

#include <GL/glew.h>
#include <future>
#include <mutex>
#include <vector>
#include "Util/GLMath.h"
#include "Terrain/TerrainSquare.h"
#include "Terrain/BoxCoord.h"
#include "Main/Settings.h"

class Terrain {
	const int SIZE_OF_FLOAT = sizeof(GLfloat);
	const int SQUARE_FLOAT_COUNT = TERRAIN_SQUARE_SIZE * TERRAIN_SQUARE_SIZE * 18;
	const int TOTAL_BUFFER_COUNT = SQUARE_FLOAT_COUNT * 9;
	const int TOTAL_FLOAT_COUNT = TOTAL_BUFFER_COUNT / 3;

	Vector3f color;

	std::vector<TerrainSquare> squares;
	std::vector<TerrainSquare> squaresToBuffer;
	std::vector<BoxCoord> squareCoordList;
	std::vector<std::future<void>*> futures;

	BoxCoord* memory[9];

	TerrainSquare prev;

	GLuint VAO;

	GLint sPositionHandle, sNormalHandle, sColorHandle, sSunHandle, sMVPHandle;

	GLuint shaderProgram;

	GLuint vboTerrainVertexHandle, vboTerrainNormalHandle;

	static Vector2f fountainLocation;
	static float fountainHeight;
	static int fountainRadius;

	std::mutex generatorMutex;

public:
	Terrain();

	Terrain(Vector2f startPosition);

	BoxCoord getSquareCoord(float x, float z);

	TerrainSquare* getSquareAt(float x, float y);

	void draw(Matrix4f projection, Matrix4f view, Vector3f sunDirection);

	void update(Vector3f pos);

	std::future<void>* addSquare(int x, int y);

	void deleteSquare(TerrainSquare square);

	TerrainSquare* getSquare(int x, int y);

	int getAvailableSquare();

	float getHeightAt(float x, float y);

	Vector2f getCenterOfInfluence();

	bool isFountainPlaced();

	int getInfluenceRadius();

	void placeFountain(int x, int z, int r);

	void updateVBO();
};

#endif