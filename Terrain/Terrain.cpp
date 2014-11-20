#include "Terrain/Terrain.h"
#include "Util/ShaderUtil.h"
#include "Util/Utility.h"
#include "Util/TerrainUtil.h"
#include "Terrain/TerrainSquare.h"
#include "Main/WorldState.h"
#include <climits>
#include <future>


Terrain::Terrain(Player& player) {
	
	trees = new std::list<Tree>();

	settlements = new std::vector<Settlement>();

	//------------------------------------------------------------------------------
	// Generate Noise
	//------------------------------------------------------------------------------
	std::srand(GAME_SEED);
	for(int i = 0; i < NOISE_SIZE; i++) {
		for(int j = 0; j < NOISE_SIZE; j++) {
			NOISE[i][j] = std::rand();
		}
	}

	//------------------------------------------------------------------------------
	// Initialize Memory
	//------------------------------------------------------------------------------
	for(int i = 0; i < 9; i++) {
		memory[i] = Vector2i(INT_MAX, INT_MAX);
	}

	//------------------------------------------------------------------------------
	// Create and Bind VAO
	//------------------------------------------------------------------------------
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//------------------------------------------------------------------------------
	// Create Shader Program
	//------------------------------------------------------------------------------
	std::vector<GLenum> shadersUsed = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };
	shaderProgram = ShaderUtil::createProgram("Terrain", shadersUsed, true);

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
	vertexVBO = buffs[0];
	normalVBO = buffs[1];

	//------------------------------------------------------------------------------
	// Allocate Memory for Position Data
	//------------------------------------------------------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, TOTAL_BUFFER_COUNT * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(sPositionHandle);
	glVertexAttribPointer(sPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//------------------------------------------------------------------------------
	// Allocate Memory for Normal Data
	//------------------------------------------------------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, TOTAL_BUFFER_COUNT * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(sNormalHandle);
	glVertexAttribPointer(sNormalHandle, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Vector2i currSquare = getSquareCoord(player.getPosition());

	for(int i = -1; i <= 1; i++) {
		for(int j = -1; j <= 1; j++) {
			addSquare(currSquare + Vector2i(i, j));
		}
	}

	prevSquare = currSquare;

	for(auto& kv : futureSquares) {
		kv.second->wait();
		TerrainSquare s = kv.second->get();

		int n = getAvailableSquare();

		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferSubData(GL_ARRAY_BUFFER,
			SQUARE_FLOAT_COUNT * sizeof(GLfloat) * n,
			SQUARE_FLOAT_COUNT * sizeof(GLfloat),
			&((*s.vertices)[0]));

		glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
		glBufferSubData(GL_ARRAY_BUFFER,
			SQUARE_FLOAT_COUNT * sizeof(GLfloat) * n,
			SQUARE_FLOAT_COUNT * sizeof(GLfloat),
			&((*s.normals)[0]));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		delete s.normals;
		delete s.vertices;

		memory[n] = kv.first;

		delete kv.second;
	}

	futureSquares.clear();

}

void Terrain::update(Player& player) {
	Vector2i currSquare = getSquareCoord(player.getPosition());

	if(currSquare != prevSquare) {

		std::cout << currSquare << std::endl;

		if(currSquare.x > prevSquare.x) {
			deleteSquare(Vector2i(prevSquare.x - 1, prevSquare.y));
			deleteSquare(Vector2i(prevSquare.x - 1, prevSquare.y - 1));
			deleteSquare(Vector2i(prevSquare.x - 1, prevSquare.y + 1));

			addSquare(Vector2i(currSquare.x + 1,	currSquare.y));
			addSquare(Vector2i(currSquare.x + 1,	currSquare.y - 1));
			addSquare(Vector2i(currSquare.x + 1,	currSquare.y + 1));
		} else if(currSquare.x < prevSquare.x) {
			deleteSquare(Vector2i(prevSquare.x + 1, prevSquare.y));
			deleteSquare(Vector2i(prevSquare.x + 1, prevSquare.y - 1));
			deleteSquare(Vector2i(prevSquare.x + 1, prevSquare.y + 1));

			addSquare(Vector2i(currSquare.x - 1,	currSquare.y));
			addSquare(Vector2i(currSquare.x - 1,	currSquare.y - 1));
			addSquare(Vector2i(currSquare.x - 1,	currSquare.y + 1));
		}

		if(currSquare.y > prevSquare.y) {
			deleteSquare(Vector2i(prevSquare.x,		prevSquare.y - 1));
			deleteSquare(Vector2i(prevSquare.x - 1,	prevSquare.y - 1));
			deleteSquare(Vector2i(prevSquare.x + 1,	prevSquare.y - 1));

			addSquare(Vector2i(currSquare.x,		currSquare.y + 1));
			addSquare(Vector2i(currSquare.x - 1,	currSquare.y + 1));
			addSquare(Vector2i(currSquare.x + 1,	currSquare.y + 1));
		} else if(currSquare.y < prevSquare.y) {
			deleteSquare(Vector2i(prevSquare.x,		prevSquare.y + 1));
			deleteSquare(Vector2i(prevSquare.x - 1, prevSquare.y + 1));
			deleteSquare(Vector2i(prevSquare.x + 1, prevSquare.y + 1));

			addSquare(Vector2i(currSquare.x,		currSquare.y - 1));
			addSquare(Vector2i(currSquare.x - 1,	currSquare.y - 1));
			addSquare(Vector2i(currSquare.x + 1,	currSquare.y - 1));
		}
		prevSquare = currSquare;
	}

	for(auto& kv : futureSquares) {
		if(kv.second->wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			TerrainSquare s = kv.second->get();

			int n = getAvailableSquare();

			glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
			glBufferSubData(GL_ARRAY_BUFFER,
				SQUARE_FLOAT_COUNT * sizeof(GLfloat) * n,
				SQUARE_FLOAT_COUNT * sizeof(GLfloat),
				&((*s.vertices)[0]));

			glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
			glBufferSubData(GL_ARRAY_BUFFER,
				SQUARE_FLOAT_COUNT * sizeof(GLfloat) * n,
				SQUARE_FLOAT_COUNT * sizeof(GLfloat),
				&((*s.normals)[0]));
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			delete s.normals;
			delete s.vertices;

			memory[n] = kv.first;

			delete kv.second;

			futureSquares.erase(kv.first);
			break;
		}
	}

}

void Terrain::draw(Camera& camera, Sun& sun) {
	//------------------------------------------------------------------------------
	// Create MVP Matrix
	//------------------------------------------------------------------------------
	Matrix4f MVP = camera.getProjection() * camera.getView();

	glBindVertexArray(VAO);

	//------------------------------------------------------------------------------
	// Tell OGL to use Shader Program
	//------------------------------------------------------------------------------
	glUseProgram(shaderProgram);

	//------------------------------------------------------------------------------
	// Load Color
	//------------------------------------------------------------------------------
	glUniform3f(sColorHandle, 0.36f, 0.25f, 0.2f);

	//------------------------------------------------------------------------------
	// Load Sun Position
	//------------------------------------------------------------------------------
	glUniform3f(sSunHandle, sun.getPosition().x, sun.getPosition().y, 0);

	//------------------------------------------------------------------------------
	// Load MVP Matrix 
	//------------------------------------------------------------------------------
	GLfloat arr[16];
	MVP.asArray(arr);
	glUniformMatrix4fv(sMVPHandle, 1, GL_TRUE, arr);

	//------------------------------------------------------------------------------
	// Draw
	//------------------------------------------------------------------------------
	glDrawArrays(GL_TRIANGLES, 0, TOTAL_VERT_COUNT);

	//------------------------------------------------------------------------------
	// Unbind / Disable Code
	//------------------------------------------------------------------------------
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	for(auto& s : *settlements) {
		s.draw(camera, sun);
	}

	for(auto& t : *trees) {
		t.draw(camera, sun);
	}
}

float Terrain::getHeightAt(float x, float y) {
	for(auto& s : *settlements) {
		if(GLMath::intersect(Vector2f(x, y), s.getArea()))
			return s.getHeight();
	}
	return TerrainUtil::octivate(TERRAIN_NUM_OCTIVES, TERRAIN_INITIAL_FREQUENCY, x, y, NOISE) * (float) TERRAIN_HEIGHT;
}

float Terrain::getHeightAt(Vector2f v) {
	return getHeightAt(v.x, v.y);
}

void Terrain::addSquare(Vector2i coord) {

	// Check is square exists in memory
	for(int i = 0; i < 9; i++) {
		if(memory[i] == coord)
			return;
	}
	for(auto& kv : futureSquares) {
		if(coord == kv.first)
			return;
	}
	
	Utility::printToOutput(coord.toString() + " added\n");

	// Add Square
	futureSquares[coord] = new std::future<TerrainSquare>(std::async(std::launch::async, Terrain::generateTerrain, coord, NOISE, *settlements));
	
}

void Terrain::addPlayerSettlement(Player& player, float radius) {
	Circle c(Vector2f(player.getPosition().x, player.getPosition().z), radius);
	settlements->push_back(Settlement(c, getHeightAt(c.center)));
	Settlement* s = &(*settlements)[settlements->size() - 1];
	std::vector<Vector2i> affectedSquares;
	for(int i = -1; i <= 1; i++) {
		for(int j = -1; j <= 1; j++) {
			Vector2i square = prevSquare + Vector2i(i, j);
			Vector2i p = square * TERRAIN_SQUARE_SIZE;
			Rect r(p, p + Vector2i(TERRAIN_SQUARE_SIZE, TERRAIN_SQUARE_SIZE));

			if(GLMath::intersect(s->getArea(), r) && !Utility::contains(affectedSquares, square)) {
				deleteSquare(square);
				addSquare(square);
				affectedSquares.push_back(square);
			}
		}
	}
	
	player.setSettlement(s);
}

void Terrain::addTree(Vector2f pos) {
	trees->push_back(Tree(Vector3f(pos.x, getHeightAt(pos), pos.y)));
}

void Terrain::deleteSquare(Vector2i coord) {
	for(int i = 0; i < 9; i++) {
		if(memory[i] == coord) {
			memory[i] = Vector2i(INT_MAX, INT_MAX);
			Utility::printToOutput(coord.toString() + " deleted\n");
			return;
		}
	}
	if(futureSquares.erase(coord))
		Utility::printToOutput(coord.toString() + " deletedn\n");
}

int Terrain::getAvailableSquare() {
	for(int i = 0; i < 9; i++) {
		if(memory[i] == Vector2i(INT_MAX, INT_MAX))
			return i;
	}
	return -1;
}

Vector2i Terrain::getSquareCoord(Vector3f pos) {
	int sx, sz;
	if(pos.x >= 0)
		sx = (int) pos.x / TERRAIN_SQUARE_SIZE;
	else
		sx = ((int) pos.x / TERRAIN_SQUARE_SIZE) - 1;
	if(pos.z >= 0)
		sz = (int) pos.z / TERRAIN_SQUARE_SIZE;
	else
		sz = ((int) pos.z / TERRAIN_SQUARE_SIZE) - 1;

	return Vector2i(sx, sz);
}

TerrainSquare Terrain::generateTerrain(Vector2i coord, int NOISE[NOISE_SIZE][NOISE_SIZE], std::vector<Settlement>& settlements) {
	Vector2f topLeftCorner = coord * TERRAIN_SQUARE_SIZE;
	
	Rect r(topLeftCorner, topLeftCorner + Vector2f(TERRAIN_SQUARE_SIZE, TERRAIN_SQUARE_SIZE));
	bool containsSettlement = false;
	for(auto& s : settlements) {
		if(GLMath::intersect(s.getArea(), r)) {
			containsSettlement = true;
			break;
		}
	}

	float yVals[TERRAIN_SQUARE_SIZE + 1][TERRAIN_SQUARE_SIZE + 1];

	float nx, ny;
	for(int i = 0; i <= TERRAIN_SQUARE_SIZE; i++) {
		for(int j = 0; j <= TERRAIN_SQUARE_SIZE; j++) {

			nx = topLeftCorner.x + i;
			ny = topLeftCorner.y + j;
			if(containsSettlement) {
				for(auto& s : settlements) {
					if(GLMath::intersect(Vector2f(nx, ny), s.getArea())) {
						yVals[i][j] = s.getHeight();
						break;
					} else {
						yVals[i][j] = TerrainUtil::octivate(TERRAIN_NUM_OCTIVES, TERRAIN_INITIAL_FREQUENCY, nx, ny, NOISE) * (float) TERRAIN_HEIGHT;
					}
				}
			} else {
				yVals[i][j] = TerrainUtil::octivate(TERRAIN_NUM_OCTIVES, TERRAIN_INITIAL_FREQUENCY, nx, ny, NOISE) * (float) TERRAIN_HEIGHT;
			}
		}
	}

	Vector3f p1, p2, p3, p4, n1, n2;

	std::vector<GLfloat>* vertices = new std::vector<GLfloat>();
	std::vector<GLfloat>* normals = new std::vector<GLfloat>();
	for(int i = 0; i < TERRAIN_SQUARE_SIZE; i++) {
		for(int j = 0; j < TERRAIN_SQUARE_SIZE; j++) {

			p1 = Vector3f(topLeftCorner.x + i, yVals[i][j], topLeftCorner.y + j);
			p2 = Vector3f(topLeftCorner.x + i, yVals[i][j + 1], topLeftCorner.y + j + 1);
			p3 = Vector3f(topLeftCorner.x + i + 1, yVals[i + 1][j + 1], topLeftCorner.y + j + 1);
			p4 = Vector3f(topLeftCorner.x + i + 1, yVals[i + 1][j], topLeftCorner.y + j);

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

	return TerrainSquare(coord, vertices, normals);
}