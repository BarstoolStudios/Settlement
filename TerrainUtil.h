#ifndef TERRAINUTIL_H
#define TERRAINUTIL_H

#include "GLMath.h"


class TerrainUtil {
	const static Vector2f gradientSet[8];

	static int NOISE[256][256];

	static float perlin(int size, float x, float y);

	static int hashX(int x);

	static int hashY(int y);

public:
	static void seedNoise(int seed);

	static float octivate(int nOctives, int size, float x, float y);

	static int random(int x, int y);

	static float hermite(float x, float y);

};

#endif