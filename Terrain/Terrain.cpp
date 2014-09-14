#include <GL\glew.h>
#include <vector>
#include <mutex>
#include <cmath>
#include <stdexcept>
#include <string>
#include <iostream>
#include <future>
#include "Terrain.h"
#include "TerrainSquare.h"
#include "TerrainGenerator.h"
#include "TerrainUtil.h"
#include "GLMath.h"
#include "BoxCoord.h"
#include "ShaderUtil.h"
#include "Utility.h"

Vector2f Terrain::fountainLocation = Vector2f(0, 0);
float Terrain::fountainHeight = 0.0f;
int Terrain::fountainRadius = -1;

Terrain::Terrain() : Terrain(Vector2f(0, 0)) {}

Terrain::Terrain(Vector2f startPosition) {
	
	color = Vector3f(0.36f, 0.25f, 0.2f);

	//------------------------------------------------------------------------------
	// Setup Helper Classes
	//------------------------------------------------------------------------------
	TerrainUtil::seedNoise(GAME_SEED);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//------------------------------------------------------------------------------
	// Create Shader Program
	//------------------------------------------------------------------------------
	shaderProgram = ShaderUtil::createProgram("Terrain", std::vector<GLenum>{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER}, true);

	//------------------------------------------------------------------------------
	// Get Shader Variable Locations
	//------------------------------------------------------------------------------
	sPositionHandle = glGetAttribLocation(shaderProgram, "iPosition");
	sNormalHandle = glGetAttribLocation(shaderProgram, "iNormal");
	sColorHandle = glGetUniformLocation(shaderProgram, "uColor");
	sSunHandle = glGetUniformLocation(shaderProgram, "uSunDirection");
	sMVPHandle = glGetUniformLocation(shaderProgram, "uMVP");

	//------------------------------------------------------------------------------
	// Generate VBOs
	//------------------------------------------------------------------------------
	GLuint buffs[2];
	glGenBuffers(2, buffs);
	vboTerrainVertexHandle = buffs[0];
	vboTerrainNormalHandle = buffs[1];

	//------------------------------------------------------------------------------
	// Allocate Memory for Position Data
	//------------------------------------------------------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vboTerrainVertexHandle);
	glBufferData(GL_ARRAY_BUFFER, TOTAL_BUFFER_COUNT * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	//------------------------------------------------------------------------------
	// Allocate Memory for Normal Data
	//------------------------------------------------------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vboTerrainNormalHandle);
	glBufferData(GL_ARRAY_BUFFER, TOTAL_BUFFER_COUNT * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	BoxCoord currSquare = getSquareCoord(startPosition.x, startPosition.y);

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			TerrainGenerator gen(currSquare.x + i, currSquare.y + j, squaresToBuffer, generatorMutex);
			futures.push_back(gen.start());
		}
	}

	for(auto future : futures) {
		future->wait();
		delete future;
	}

	futures.clear();

	int n = 0;

	for (auto& square : squaresToBuffer) {
		//------------------------------------------------------------------------------
		// Buffer Position Data for Squares Into VBO
		//------------------------------------------------------------------------------
		glBindBuffer(GL_ARRAY_BUFFER, vboTerrainVertexHandle);
		glBufferSubData(GL_ARRAY_BUFFER,
						SQUARE_FLOAT_COUNT * sizeof(GLfloat) * n,
						SQUARE_FLOAT_COUNT * sizeof(GLfloat), 
						&((*square.vertices)[0]));

		//------------------------------------------------------------------------------
		// Buffer Normal Data for Squares Into VBO
		//------------------------------------------------------------------------------
		glBindBuffer(GL_ARRAY_BUFFER, vboTerrainNormalHandle);
		glBufferSubData(GL_ARRAY_BUFFER,
						SQUARE_FLOAT_COUNT * sizeof(GLfloat) * n,
						SQUARE_FLOAT_COUNT * sizeof(GLfloat),
						&((*square.normals)[0]));

		delete square.vertices;
		delete square.normals;

		squares.push_back(square);
		squareCoordList.push_back(BoxCoord(square.x, square.y));
		memory[n] = new BoxCoord(square.x, square.y);
		n++;
	}
	squaresToBuffer.clear();

	glUseProgram(shaderProgram);

	//------------------------------------------------------------------------------
	// Load Vertex Data
	//------------------------------------------------------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vboTerrainVertexHandle);
	glEnableVertexAttribArray(sPositionHandle);
	glVertexAttribPointer(sPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//------------------------------------------------------------------------------
	// Load Normal Data
	//------------------------------------------------------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vboTerrainNormalHandle);
	glEnableVertexAttribArray(sNormalHandle);
	glVertexAttribPointer(sNormalHandle, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	prev = *getSquare(currSquare.x, currSquare.y);

}

BoxCoord Terrain::getSquareCoord(float x, float z) {
	int sx, sz;
	if (x >= 0)
		sx = (int)x / TERRAIN_SQUARE_SIZE;
	else
		sx = ((int)x / TERRAIN_SQUARE_SIZE) - 1;
	if (z >= 0)
		sz = (int)z / TERRAIN_SQUARE_SIZE;
	else
		sz = ((int)z / TERRAIN_SQUARE_SIZE) - 1;

	return BoxCoord(sx, sz);
}

TerrainSquare* Terrain::getSquareAt(float x, float y) {
	int sx, sz;
	if (x >= 0)
		sx = (int)x / TERRAIN_SQUARE_SIZE;
	else
		sx = ((int)x / TERRAIN_SQUARE_SIZE) - 1;
	if (y >= 0)
		sz = (int)y / TERRAIN_SQUARE_SIZE;
	else
		sz = ((int)y / TERRAIN_SQUARE_SIZE) - 1;

	for (TerrainSquare& square : squares) {
		if (square.x == sx && square.y == sz) {
			return &square;
		}
	}
	throw std::invalid_argument(std::string("Square containing (") + std::to_string(x) + ", " + std::to_string(y) + ") is not loaded");
}

void Terrain::draw(Matrix4f projection, Matrix4f view, Vector3f sunDirection) {
	//------------------------------------------------------------------------------
	// Create MVP Matrix
	//------------------------------------------------------------------------------
	Matrix4f MVP = projection * view;

	glBindVertexArray(VAO);

	//------------------------------------------------------------------------------
	// Tell OGL to use Shader Program
	//------------------------------------------------------------------------------
	glUseProgram(shaderProgram);

	//------------------------------------------------------------------------------
	// Load Color
	//------------------------------------------------------------------------------
	glUniform3f(sColorHandle, color.x, color.y, color.z);

	//------------------------------------------------------------------------------
	// Load Sun Position
	//------------------------------------------------------------------------------
	glUniform3f(sSunHandle, sunDirection.x, sunDirection.y, sunDirection.z);

	//------------------------------------------------------------------------------
	// Load MVP Matrix 
	//------------------------------------------------------------------------------
	GLfloat arr[16];
	MVP.asArray(arr);
	glUniformMatrix4fv(sMVPHandle, 1, GL_TRUE, arr);

	//------------------------------------------------------------------------------
	// Draw
	//------------------------------------------------------------------------------
	glDrawArrays(GL_TRIANGLES, 0, TOTAL_FLOAT_COUNT);

	//------------------------------------------------------------------------------
	// Unbind / Disable Code
	//------------------------------------------------------------------------------
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Terrain::update(Vector3f pos) {
	TerrainSquare curr = *getSquareAt(pos.x, pos.z);

	if (curr != prev) {
		std::cout << curr.toString() <<'\n';
		if (curr.x > prev.x) {
			addSquare(curr.x + 1, curr.y);
			addSquare(curr.x + 1, curr.y - 1);
			addSquare(curr.x + 1, curr.y + 1);
		}
		else if (curr.x < prev.x) {
			addSquare(curr.x - 1, curr.y);
			addSquare(curr.x - 1, curr.y - 1);
			addSquare(curr.x - 1, curr.y + 1);
		}

		if (curr.y > prev.y) {
			addSquare(curr.x, curr.y + 1);
			addSquare(curr.x - 1, curr.y + 1);
			addSquare(curr.x + 1, curr.y + 1);
		}
		else if (curr.y < prev.y){
			addSquare(curr.x, curr.y - 1);
			addSquare(curr.x - 1, curr.y - 1);
			addSquare(curr.x + 1, curr.y - 1);
		}
		prev = curr;
	}

	std::vector<TerrainSquare> squaresToRemove;
	for (TerrainSquare square : squares) {
		if (std::abs(square.x - curr.x) > 1 || std::abs(square.y - curr.y) > 1){
			squaresToRemove.push_back(square);
		}
	}


	for (TerrainSquare square : squaresToRemove)
		deleteSquare(square);
	
	generatorMutex.lock();
		if (squaresToBuffer.size() > 0) {
			int n = getAvailableSquare();
			if (n != -1) {
				TerrainSquare square = squaresToBuffer[0];

				glBindBuffer(GL_ARRAY_BUFFER, vboTerrainVertexHandle);
				glBufferSubData(GL_ARRAY_BUFFER,
								SQUARE_FLOAT_COUNT * sizeof(GLfloat) * n,
								SQUARE_FLOAT_COUNT * sizeof(GLfloat),
								&((*square.vertices)[0]));

				glBindBuffer(GL_ARRAY_BUFFER, vboTerrainNormalHandle);
				glBufferSubData(GL_ARRAY_BUFFER,
								SQUARE_FLOAT_COUNT * sizeof(GLfloat) * n,
								SQUARE_FLOAT_COUNT * sizeof(GLfloat),
								&((*square.normals)[0]));
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				delete square.normals;
				delete square.vertices;

				memory[n] = new BoxCoord(square.x, square.y);
				squares.push_back(square);
				squaresToBuffer.erase(squaresToBuffer.begin());
			}
		}
	generatorMutex.unlock();
}

std::future<void>* Terrain::addSquare(int x, int y) {
	BoxCoord b(x, y);
	if (!Utility::contains(squareCoordList, b)) {
		squareCoordList.push_back(b);
		TerrainGenerator gen(x, y, squaresToBuffer, generatorMutex);
		return gen.start();
	}
	return NULL;
}

void Terrain::deleteSquare(TerrainSquare square) {
		for (int i = 0; i < 9; i++) {
			if (memory[i] != NULL && memory[i]->x == square.x && memory[i]->y == square.y) {
				delete memory[i];
				memory[i] = NULL;
			}
		}
		Utility::remove(squareCoordList, BoxCoord(square.x, square.y));
		Utility::remove(squares, square);
}

TerrainSquare* Terrain::getSquare(int x, int y) {
	for (TerrainSquare& square : squares) {
		if (square.x == x && square.y == y) {
			return &square;
		}
	}
	throw std::invalid_argument(std::string("Square [") + std::to_string(x) + ", " + std::to_string(y) + "] is not loaded");
}

int Terrain::getAvailableSquare() {
	for (int i = 0; i < 9; i++) {
		if (memory[i] == NULL)
			return i;
	}
	return -1;
}

float Terrain::getHeightAt(float x, float y) {
	if (fountainRadius != -1 &&
		Utility::distThreshold(fountainLocation.x, fountainLocation.y, x, y, fountainRadius))
		return fountainHeight;
	return TerrainUtil::octivate(TERRAIN_NUM_OCTIVES, TERRAIN_INITIAL_FREQUENCY, x, y) * (float) TERRAIN_HEIGHT;
}

Vector2f Terrain::getCenterOfInfluence() {
	return fountainLocation;
}

bool Terrain::isFountainPlaced() {
	return fountainRadius != -1;
}

int Terrain::getInfluenceRadius() {
	return fountainRadius;
}

void Terrain::placeFountain(int x, int z, int r) {

}

void Terrain::updateVBO() {
	generatorMutex.lock();
		while (squaresToBuffer.size() > 0) {
			int n = getAvailableSquare();
			if (n != -1) {
				TerrainSquare square = squaresToBuffer[0];
				glBindBuffer(GL_ARRAY_BUFFER, vboTerrainVertexHandle);
				glBufferSubData(GL_ARRAY_BUFFER,
								SQUARE_FLOAT_COUNT * sizeof(GLfloat) * n,
								SQUARE_FLOAT_COUNT * sizeof(GLfloat),
								&square.vertices[0]);
				glBindBuffer(GL_ARRAY_BUFFER, vboTerrainNormalHandle);
				glBufferSubData(GL_ARRAY_BUFFER,
								SQUARE_FLOAT_COUNT * sizeof(GLfloat) * n,
								SQUARE_FLOAT_COUNT * sizeof(GLfloat),
								&square.normals[0]);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				delete square.normals;
				delete square.vertices;

				memory[n] = new BoxCoord(square.x, square.y);
				squares.push_back(square);
				squaresToBuffer.erase(squaresToBuffer.begin());
			}
		}
		generatorMutex.unlock();
}