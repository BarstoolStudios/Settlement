#ifndef CAMERA_H
#define CAMERA_H

#include "Util/GLMath.h"
#include "Types/MoveType.h"
#include "Util/GameTimer.h"
#include "Terrain/Terrain.h"
#include "Main/Mouse.h"
#include "Main/Keyboard.h"

class Camera {
	float speed;

	Vector3f position;
	Vector3f rotation;
	Vector3f previous;

	Matrix4f orthographic;
	Matrix4f perspective;
	Matrix4f view;
	Matrix3f transform2D;

	double delta;

	float yBottom;
	float yMotion;

	bool topView;

public:
	Camera();
	Camera(Vector2f pos);

	bool isOnGround();

	void update(GameTimer& timer, Terrain& terrain);

	void individualPhysics(Terrain& terrain);

	void input(Keyboard& keyboard, Mouse& mouse);

	void updatePreviousVector();

	void resetPosition();

	Matrix4f getProjection();

	Matrix4f getView();

	Matrix3f getTransform2D();

	void makeView();

	Vector3f getPosition();

	Vector3f getRotation();

	void setPosition(float x, float y, float z);

	void setRotation(float x, float y, float z);
	
	void setTopView(bool state);

	bool isTopView();

	Vector2f screenToWorld(Vector2f screenCoord, int height, int width);

	Vector2f worldToScreen(Vector2f worldCoord, int height, int width);

	void updateProjection(float fov, float height, float width, float zNear, float zFar);
};

#endif