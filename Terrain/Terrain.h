#ifndef TERRAIN_H
#define TERRAIN_H

class Terrain;

#include <map>
#include <functional>
#include <future>
#include "Main/Player.h"
#include "Main/Camera.h"
#include "Terrain/Sun.h"
#include "Util/GLMath.h"
#include "Main/Settings.h"
#include "Terrain/TerrainSquare.h"

class Terrain {

	const int SQUARE_FLOAT_COUNT = TERRAIN_SQUARE_SIZE * TERRAIN_SQUARE_SIZE * 18;
	const int TOTAL_BUFFER_COUNT = SQUARE_FLOAT_COUNT * 9;
	const int TOTAL_VERT_COUNT = TOTAL_BUFFER_COUNT / 3;

	GLuint VAO;

	GLint sPositionHandle, sNormalHandle, sColorHandle, sSunHandle, sMVPHandle;

	GLuint shaderProgram;

	GLuint vertexVBO, normalVBO;

	Vector2i prevSquare;

	Vector2i memory[9];

	struct vecComp {
		bool operator () (const Vector2i& v1, const Vector2i& v2) const 
		{if(v1.x == v2.x) return v1.y < v2.y; return v1.x < v2.x;}
	};

	std::map<Vector2i, std::future<TerrainSquare>*, vecComp> futureSquares;

public:

	const static int NOISE_SIZE = 256;

	Terrain(Player& player);

	void update(Player& player);

	void draw(Camera& camera, Sun& sun);

	float getHeightAt(float x, float y);

	void addSquare(Vector2i coord);

	void deleteSquare(Vector2i coord);

	int getAvailableSquare();

	Vector2i getSquareCoord(Vector3f pos);

	static TerrainSquare generateTerrain(Vector2i coord, int NOISE[NOISE_SIZE][NOISE_SIZE]);

private:
	int NOISE[NOISE_SIZE][NOISE_SIZE];
};

#endif // TERRAIN_H