#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "Camera.h"
#include "GLMath.h"
#include "Settings.h"
#include "Mouse.h"
#include "Keyboard.h"

Camera::Camera() : Camera(Vector2f(0,0)) {}

Camera::Camera(Vector2f pos) :	position(pos.x, 0, pos.y), 
								previous(pos.x, 0, pos.y),
								yBottom(0),
								yMotion(0),
								topView(false),
								speed(CAMERA_RUN_SPEED)
{
	perspective = GLMath::getPerspective(CAMERA_FOV, DISPLAY_INITIAL_HEIGHT, DISPLAY_INITIAL_WIDTH, CAMERA_ZNEAR, CAMERA_ZFAR);
	orthographic = GLMath::getOrthographic(DISPLAY_INITIAL_HEIGHT, DISPLAY_INITIAL_WIDTH, CAMERA_ZNEAR, CAMERA_ZFAR, CAMERA_ORTHO_SCALING);
	transform2D = GLMath::getTransform2D(DISPLAY_INITIAL_HEIGHT, DISPLAY_INITIAL_WIDTH);

	makeView();
}

bool Camera::isOnGround() {
	return position.y <= yBottom;
}

void Camera::update(GameTimer& timer, Terrain& terrain) {
	makeView();
	//delta = timer.getDelta();
	delta = 16;
	updateMotion();
	individualPhysics(terrain);
	updatePreviousVector();
}

void Camera::individualPhysics(Terrain& terrain) {
	yBottom = terrain.getHeightAt(position.x, position.z);

	position.y += yMotion;
	if (position.y > yBottom){
		yMotion -= CAMERA_GRAVITY * (float)delta;
	}
	if (position.y <= yBottom){
		position.y = yBottom;
		yMotion = 0;
	}
}

void Camera::input(Keyboard& keyboard, Mouse& mouse) {

	if(keyboard.isKeyDown(Keyboard::KEY_LSHIFT)) {
		speed = CAMERA_SPRINT_SPEED;

	} else if(keyboard.isKeyDown(Keyboard::KEY_LCTRL)) {
		speed = CAMERA_WALK_SPEED;

	} else {
		speed = CAMERA_RUN_SPEED;

	}

	if(keyboard.isKeyDown(Keyboard::KEY_W) && !keyboard.isKeyDown(Keyboard::KEY_A) &&
		!keyboard.isKeyDown(Keyboard::KEY_D)) {
		position.x += sin(rotation.y*M_PI / 180) * speed * delta;
		position.z += -cos(rotation.y*M_PI / 180) * speed * delta;

	} else if(keyboard.isKeyDown(Keyboard::KEY_A) && !keyboard.isKeyDown(Keyboard::KEY_W) &&
		!keyboard.isKeyDown(Keyboard::KEY_S)) {
		position.x += sin((rotation.y - 90)*M_PI / 180) * speed * delta;
		position.z += -cos((rotation.y - 90)*M_PI / 180) * speed * delta;

	} else if(keyboard.isKeyDown(Keyboard::KEY_S) && !keyboard.isKeyDown(Keyboard::KEY_A) &&
		!keyboard.isKeyDown(Keyboard::KEY_D)) {
		position.x += -sin(rotation.y*M_PI / 180) * speed * delta;
		position.z += cos(rotation.y*M_PI / 180) * speed * delta;

	} else if(keyboard.isKeyDown(Keyboard::KEY_D) && !keyboard.isKeyDown(Keyboard::KEY_W) &&
		!keyboard.isKeyDown(Keyboard::KEY_S)) {
		position.x += sin((rotation.y + 90)*M_PI / 180) * speed * delta;
		position.z += -cos((rotation.y + 90)*M_PI / 180) * speed * delta;

	} else if(keyboard.isKeyDown(Keyboard::KEY_A) && keyboard.isKeyDown(Keyboard::KEY_W)) {
		position.x += sin((rotation.y - 45)*M_PI / 180) * speed * delta;
		position.z += -cos((rotation.y - 45)*M_PI / 180) * speed * delta;

	} else if(keyboard.isKeyDown(Keyboard::KEY_D) && keyboard.isKeyDown(Keyboard::KEY_W)) {
		position.x += sin((rotation.y + 45)*M_PI / 180) * speed * delta;
		position.z += -cos((rotation.y + 45)*M_PI / 180) * speed * delta;

	} else if(keyboard.isKeyDown(Keyboard::KEY_A) && keyboard.isKeyDown(Keyboard::KEY_S)) {
		position.x += -sin((rotation.y + 45)*M_PI / 180) * speed * delta;
		position.z += cos((rotation.y + 45)*M_PI / 180) * speed * delta;

	} else if(keyboard.isKeyDown(Keyboard::KEY_D) && keyboard.isKeyDown(Keyboard::KEY_S)) {
		position.x += -sin((rotation.y - 45)*M_PI / 180) * speed * delta;
		position.z += cos((rotation.y - 45)*M_PI / 180) * speed * delta;

	}


	if(keyboard.isKeyDown(Keyboard::KEY_SPACE)) {
		yMotion += 0.04f;
	}

	if (mouse.isGrabbed()) {
		float mouseDX = mouse.getDX() * 0.8f * 0.16f;
		float mouseDY = mouse.getDY() * 0.8f * 0.16f;

		rotation.y += mouseDX;
		rotation.x += mouseDY;

		// keep Y rotation in the range [0, 360)
		if (rotation.y >= 360)
			rotation.y -= 360;
		else if (rotation.y < 0)
			rotation.y += 360;
		
		// Limit head motion between [-85, 85]
		if (rotation.x  < -85)
			rotation.x = -85;
		else if (rotation.x  > 85)
			rotation.x = 85;
		
	}
}

void Camera::updatePreviousVector() {
	previous.x = position.x;
	previous.y = position.y;
	previous.z = position.z;
}

void Camera::resetPosition() {
	position.x = previous.x;
	position.y = previous.y;
	position.z = previous.z;
}

void Camera::updateMotion() {

}

Matrix4f Camera::getProjection() {
	return (topView ? orthographic : perspective);
}

Matrix4f Camera::getView() {
	return view;
}

Matrix3f Camera::getTransform2D() {
	return transform2D;
}

void Camera::makeView() {
	if (!topView) {
		Matrix4f rot = GLMath::getRotation(rotation.x, rotation.y, rotation.z);
		Matrix4f trans = GLMath::getTranslation(-position.x, -position.y - CAMERA_PLAYER_HEIGHT, -position.z);
		view = rot * trans;
	}else {
		Matrix4f rot = GLMath::getRotation(90, rotation.y, rotation.z);
		Matrix4f trans = GLMath::getTranslation(-position.x, -position.y - CAMERA_FLY_HEIGHT, -position.z);
		view = rot * trans;
	}
}

Vector3f Camera::getPosition() {
	return position;
}

Vector3f Camera::getRotation() {
	return rotation;
}

void Camera::setPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

void Camera::setRotation(float x, float y, float z) {
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

void Camera::setTopView(bool state) {
	topView = state;
}

bool Camera::isTopView() {
	return topView;
}

Vector2f Camera::screenToWorld(Vector2f screenCoord, int height, int width) {
	return Vector2f(((screenCoord.x - (width / 2)) / CAMERA_ORTHO_SCALING) + position.x
		, (((height / 2) - screenCoord.y) / CAMERA_ORTHO_SCALING) + position.z);
}

Vector2f Camera::worldToScreen(Vector2f worldCoord, int height, int width) {
	return Vector2f(((worldCoord.x - position.x) * CAMERA_ORTHO_SCALING) + (width / 2),
		((height / 2) - (worldCoord.y - position.y) * CAMERA_ORTHO_SCALING));
}

void Camera::updateProjection(float fov, float height, float width, float zNear, float zFar) {
	perspective = GLMath::getPerspective(fov, height, width, zNear, zFar);
	orthographic = GLMath::getOrthographic(height, width, zNear, zFar, CAMERA_ORTHO_SCALING);
}