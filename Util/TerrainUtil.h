#ifndef TERRAINUTIL_H
#define TERRAINUTIL_H

class TerrainUtil;

#include "Util/GLMath.h"
#include "Main/Settings.h"
#include "Terrain/Terrain.h"

class TerrainUtil {
	const static Vector2f gradientSet[8];

	static float perlin(int size, float x, float y, int NOISE[Terrain::NOISE_SIZE][Terrain::NOISE_SIZE]);

	static int hashX(int x);

	static int hashY(int y);

	static int random(int x, int y, int NOISE[Terrain::NOISE_SIZE][Terrain::NOISE_SIZE]);

	static float hermite(float x, float y);

public:

	static float octivate(int nOctives, int size, float x, float y, int NOISE[Terrain::NOISE_SIZE][Terrain::NOISE_SIZE]);

};

#endif