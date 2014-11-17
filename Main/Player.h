#ifndef PLAYER_H
#define PLAYER_H

class Player;

#include "Util/GLMath.h"
#include "Main/Settings.h"
#include "Main/Keyboard.h"
#include "Main/Mouse.h"
#include "Terrain/Terrain.h"
#include "Util/GameTimer.h"

class Player {

	float speed;

	Vector3f position;
	Vector3f rotation;
	Vector3f previous;

	float yVelocity;

public:

	Player()
	:
		position(0, 0, 0),
		rotation(0, 0, 0),
		previous(0, 0, 0),
		yVelocity(0),
		speed(PLAYER_RUN_SPEED)
	{}

	Player(Vector3f position)
	:
		position(position),
		rotation(0, 0, 0),
		previous(position),
		yVelocity(0)
	{}

	void setPosition(Vector3f pos);
	void setPosition(float x, float y, float z);

	Vector3f getPosition();

	void setRotation(Vector3f rot);
	void setRotation(float x, float y, float z);

	Vector3f getRotation();

	void resetPosition();

	void updatePrevious();

	void applyPhysics(Terrain& terrain, GameTimer& timer);

	void input(Keyboard& keyboard, Mouse& mouse, GameTimer& timer);

	void update(Terrain& terrain, GameTimer& timer);

};

#endif // PLAYER_H