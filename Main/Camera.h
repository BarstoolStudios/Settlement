#ifndef CAMERA_H
#define CAMERA_H

class Camera;

#include "Util/GLMath.h"
#include "Types/MoveType.h"
#include "Util/GameTimer.h"
#include "Terrain/Terrain.h"
#include "Main/Mouse.h"
#include "Main/Keyboard.h"
#include "Main/Player.h"

class Camera {

	Vector3f position;
	Vector3f rotation;

	Matrix4f orthographic;
	Matrix4f perspective;
	Matrix4f view;
	Matrix3f transform2D;

	bool topView;

public:
	Camera();

	void update(Player& player);

	Matrix4f getProjection();

	Matrix4f getView();

	Matrix3f getTransform2D();

	void makeView();
	
	void setTopView(bool state);

	bool isTopView();

	Vector2f screenToWorld(Vector2f screenCoord, int height, int width);

	Vector2f worldToScreen(Vector2f worldCoord, int height, int width);

	void updateProjection(float fov, float height, float width, float zNear, float zFar);
};

#endif // CAMERA_H