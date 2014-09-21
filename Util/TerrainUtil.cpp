#include <cstdlib>
#include <cmath>
#include "Util/TerrainUtil.h"
#include "Util/GLMath.h"

const Vector2f TerrainUtil::gradientSet[] = { Vector2f(0, 1), Vector2f(1, 1), Vector2f(1, 0), Vector2f(1, -1), 
Vector2f(0, -1), Vector2f(-1, -1), Vector2f(-1, 0), Vector2f(-1, 1)};

int TerrainUtil::NOISE[256][256];

//==============================================================================
// Returns Perlin Noise Value at (x, y)
//==============================================================================
float TerrainUtil::perlin(int size, float x, float y) {
	int nx, ny;
	if (x < 0)
		nx = (((int)x / size) * size) - size;
	else
		nx = (((int)x / size) * size);

	if (y < 0)
		ny = (((int)y / size) * size);
	else
		ny = (((int)y / size) * size) + size;

	int p00[]{nx, ny};
	int p10[]{p00[0] + size, p00[1]};
	int p01[]{p00[0], p00[1] - size};
	int p11[]{p00[0] + size, p00[1] - size};

	Vector2f g00 = gradientSet[random(p00[0], p00[1]) % 8];
	Vector2f g10 = gradientSet[random(p10[0], p10[1]) % 8];
	Vector2f g01 = gradientSet[random(p01[0], p01[1]) % 8];
	Vector2f g11 = gradientSet[random(p11[0], p11[1]) % 8];

	Vector2f p = Vector2f((x - p00[0]) / size, (p00[1] - y) / size);

	Vector2f s00 = Vector2f( -p.x, -p.y );
	Vector2f s10 = Vector2f( 1 - p.x, -p.y );
	Vector2f s01 = Vector2f( -p.x, 1 - p.y );
	Vector2f s11 = Vector2f( 1 - p.x, 1 - p.y );

	float d00 = Vector2f::dot(g00, s00);
	float d10 = Vector2f::dot(g10, s10);
	float d01 = Vector2f::dot(g01, s01);
	float d11 = Vector2f::dot(g11, s11);

	float w00 = hermite(1 - p.x, 1 - p.y);
	float w10 = hermite(p.x, 1 - p.y);
	float w01 = hermite(1 - p.x, p.y);
	float w11 = hermite(p.x, p.y);

	w00 *= d00;
	w10 *= d10;
	w01 *= d01;
	w11 *= d11;

	float value = w00 + w10 + w01 + w11;

	return (value + 1) / 2.0f;
}

//==============================================================================
// Creates Hash Value for x
//==============================================================================
int TerrainUtil::hashX(int x) {
	x += (x << 10);
	x ^= (x >> 6);
	x += (x << 3);
	x ^= (x >> 11);
	x += (x << 15);
	return x;
}

//==============================================================================
// Creates Hash Value for y
//==============================================================================
int TerrainUtil::hashY(int y) {
	y += (y << 10);
	y ^= (y >> 6);
	y += (y << 10);
	y ^= (y >> 6);
	y += (y << 3);
	y ^= (y >> 11);
	y += (y << 15);
	return y;
}

//==============================================================================
// Seeds NOISE with Random Ints Based on Game Seed
//==============================================================================
void TerrainUtil::seedNoise(int seed) {
	std::srand(seed);
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			NOISE[i][j] = std::rand();
		}
	}
}

//==============================================================================
// Layers Octives of Perlin Noise
//==============================================================================
float TerrainUtil::octivate(int nOctives, int size, float x, float y) {
	float oct = 0;
	float amplitude = 0.5f;
	int freq = 2;
	for (int i = 0; i < nOctives; i++) {
		oct += (perlin(size / freq, x, y) * amplitude);
		amplitude *= 0.5f;
		freq *= 2;
	}
	return oct;
}

//==============================================================================
// Generates Random Number Based on Hashes of x and y accessing NOISE
//==============================================================================
int TerrainUtil::random(int x, int y) {
	return NOISE[std::abs(hashX(x + 1301081)) % 256][std::abs(hashY(y + 2751557)) % 256];
}

//==============================================================================
// 5th Order Hermite Function (6x^5 - 15x^4 + 10x^4) - (6y^5 - 15y^4 + 10y^4)
//==============================================================================
float TerrainUtil::hermite(float x, float y) {
	return ((10 - ((15 - 6 * x) * x)) * x * x * x) * ((10 - ((15 - 6 * y) * y)) * y * y * y);
}