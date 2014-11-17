#include "Main/Player.h"

void Player::setPosition(Vector3f pos) {
	position = pos;
}
void Player::setPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

Vector3f Player::getPosition() {
	return position;
}

void Player::setRotation(Vector3f rot) {
	rotation = rot;
}
void Player::setRotation(float x, float y, float z) {
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

Vector3f Player::getRotation() {
	return rotation;
}

void Player::resetPosition() {
	position = previous;
}

void Player::updatePrevious() {
	previous = position;
}

void Player::applyPhysics(Terrain& terrain, GameTimer& timer) {
	float dt = timer.getDelta();

	float yBottom = terrain.getHeightAt(position.x, position.z);

	position.y += yVelocity;
	if(position.y > yBottom) {
		yVelocity -= WORLD_GRAVITY * dt;
	}
	if(position.y <= yBottom) {
		position.y = yBottom;
		yVelocity = 0;
	}
}

void Player::input(Keyboard& keyboard, Mouse& mouse, GameTimer& timer) {
	float dt = timer.getDelta();


	if(keyboard.isKeyDown(Keyboard::KEY_LSHIFT)) {
		speed = PLAYER_SPRINT_SPEED;

	} else if(keyboard.isKeyDown(Keyboard::KEY_LCTRL)) {
		speed = PLAYER_WALK_SPEED;

	} else {
		speed = PLAYER_RUN_SPEED;

	}

	if(keyboard.isKeyDown(Keyboard::KEY_W) && !keyboard.isKeyDown(Keyboard::KEY_A) &&
		!keyboard.isKeyDown(Keyboard::KEY_D)) {
		position.x += sin(rotation.y*PI_F / 180) * speed * dt;
		position.z += -cos(rotation.y*PI_F / 180) * speed * dt;

	} else if(keyboard.isKeyDown(Keyboard::KEY_A) && !keyboard.isKeyDown(Keyboard::KEY_W) &&
		!keyboard.isKeyDown(Keyboard::KEY_S)) {
		position.x += sin((rotation.y - 90)*PI_F / 180) * speed * dt;
		position.z += -cos((rotation.y - 90)*PI_F / 180) * speed * dt;

	} else if(keyboard.isKeyDown(Keyboard::KEY_S) && !keyboard.isKeyDown(Keyboard::KEY_A) &&
		!keyboard.isKeyDown(Keyboard::KEY_D)) {
		position.x += -sin(rotation.y*PI_F / 180) * speed * dt;
		position.z += cos(rotation.y*PI_F / 180) * speed * dt;

	} else if(keyboard.isKeyDown(Keyboard::KEY_D) && !keyboard.isKeyDown(Keyboard::KEY_W) &&
		!keyboard.isKeyDown(Keyboard::KEY_S)) {
		position.x += sin((rotation.y + 90)*PI_F / 180) * speed * dt;
		position.z += -cos((rotation.y + 90)*PI_F / 180) * speed * dt;

	} else if(keyboard.isKeyDown(Keyboard::KEY_A) && keyboard.isKeyDown(Keyboard::KEY_W)) {
		position.x += sin((rotation.y - 45)*PI_F / 180) * speed * dt;
		position.z += -cos((rotation.y - 45)*PI_F / 180) * speed * dt;

	} else if(keyboard.isKeyDown(Keyboard::KEY_D) && keyboard.isKeyDown(Keyboard::KEY_W)) {
		position.x += sin((rotation.y + 45)*PI_F / 180) * speed * dt;
		position.z += -cos((rotation.y + 45)*PI_F / 180) * speed * dt;

	} else if(keyboard.isKeyDown(Keyboard::KEY_A) && keyboard.isKeyDown(Keyboard::KEY_S)) {
		position.x += -sin((rotation.y + 45)*PI_F / 180) * speed * dt;
		position.z += cos((rotation.y + 45)*PI_F / 180) * speed * dt;

	} else if(keyboard.isKeyDown(Keyboard::KEY_D) && keyboard.isKeyDown(Keyboard::KEY_S)) {
		position.x += -sin((rotation.y - 45)*PI_F / 180) * speed * dt;
		position.z += cos((rotation.y - 45)*PI_F / 180) * speed * dt;

	}


	if(keyboard.isKeyDown(Keyboard::KEY_SPACE)) {
		yVelocity += 0.04f;
	}

	if(mouse.isGrabbed()) {
		float mouseDX = mouse.getDX() * 0.8f * 0.16f;
		float mouseDY = mouse.getDY() * 0.8f * 0.16f;

		rotation.y += mouseDX;
		rotation.x += mouseDY;

		// keep Y rotation in the range [0, 360)
		if(rotation.y >= 360)
			rotation.y -= 360;
		else if(rotation.y < 0)
			rotation.y += 360;

		// Limit head motion between [-85, 85]
		if(rotation.x  < -85)
			rotation.x = -85;
		else if(rotation.x  > 85)
			rotation.x = 85;

	}
}

void Player::update(Terrain& terrain, GameTimer& timer) {
	applyPhysics(terrain, timer);
	updatePrevious();
}