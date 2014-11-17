/******************************************************************************\
* File: Camera.cpp
*
* Author: Josh Taylor
*
* Header: Camera.h
*
* Description: Camera used for perspective first person and orthographic
*              top down view.
\******************************************************************************/

#include <cmath>
#include <iostream>
#include "Main/Camera.h"
#include "Util/GLMath.h"
#include "Main/Settings.h"
#include "Main/Mouse.h"
#include "Main/Keyboard.h"

//==============================================================================
// Constructors
//==============================================================================
Camera::Camera()
:
	topView(false),
	position(0, 0, 0),
	rotation(0, 0, 0)
{
	perspective = GLMath::getPerspective(CAMERA_FOV, DISPLAY_INITIAL_HEIGHT, DISPLAY_INITIAL_WIDTH, CAMERA_ZNEAR, CAMERA_ZFAR);
	orthographic = GLMath::getOrthographic(DISPLAY_INITIAL_HEIGHT, DISPLAY_INITIAL_WIDTH, CAMERA_ZNEAR, CAMERA_ZFAR, CAMERA_ORTHO_SCALING);
	transform2D = GLMath::getTransform2D(DISPLAY_INITIAL_HEIGHT, DISPLAY_INITIAL_WIDTH);

	makeView();
}

//==============================================================================
// Updates the Camera
//==============================================================================
void Camera::update(Player& player) {
	rotation = player.getRotation();
	position = player.getPosition();

	makeView();
}

//==============================================================================
// Returns the Current Projection Matrix -- Perspective or Orthographic
//==============================================================================
Matrix4f Camera::getProjection() {
	return (topView ? orthographic : perspective);
}

//==============================================================================
// Returns the View Matrix
//==============================================================================
Matrix4f Camera::getView() {
	return view;
}

//==============================================================================
// Gets a 2D Transformation based on height and width of screen
//==============================================================================
Matrix3f Camera::getTransform2D() {
	return transform2D;
}

//==============================================================================
// Builds the View Based on Current position and rotation 
//==============================================================================
void Camera::makeView() {

	if (!topView) {
		Matrix4f rot = GLMath::getRotation(rotation.x, rotation.y, rotation.z);
		Matrix4f trans = GLMath::getTranslation(-position.x, -position.y - PLAYER_HEIGHT, -position.z);
		view = rot * trans;
	}else {
		Matrix4f rot = GLMath::getRotation(90, rotation.y, rotation.z);
		Matrix4f trans = GLMath::getTranslation(-position.x, -position.y - CAMERA_FLY_HEIGHT, -position.z);
		view = rot * trans;
	}
}

//==============================================================================
// Changes to State where Camera Looks Down and has Orthographic Projection
//==============================================================================
void Camera::setTopView(bool state) {
	topView = state;
}

//==============================================================================
// Returns Whether Camera is Currently in TopView Mode
//==============================================================================
bool Camera::isTopView() {
	return topView;
}

//==============================================================================
// Transforms Coordinates from Screen to World
//==============================================================================
Vector2f Camera::screenToWorld(Vector2f screenCoord, int height, int width) {
	return Vector2f(((screenCoord.x - (width / 2)) / CAMERA_ORTHO_SCALING) + position.x
		, (((height / 2) - screenCoord.y) / CAMERA_ORTHO_SCALING) + position.z);
}

//==============================================================================
// Transforms Coordinates from World to Screen
//==============================================================================
Vector2f Camera::worldToScreen(Vector2f worldCoord, int height, int width) {
	return Vector2f(((worldCoord.x - position.x) * CAMERA_ORTHO_SCALING) + (width / 2),
		((height / 2) - (worldCoord.y - position.y) * CAMERA_ORTHO_SCALING));
}

//==============================================================================
// Updates Projection Matrices
//==============================================================================
void Camera::updateProjection(float fov, float height, float width, float zNear, float zFar) {
	perspective = GLMath::getPerspective(fov, height, width, zNear, zFar);
	orthographic = GLMath::getOrthographic(height, width, zNear, zFar, CAMERA_ORTHO_SCALING);

	transform2D = GLMath::getTransform2D(height, width);
}