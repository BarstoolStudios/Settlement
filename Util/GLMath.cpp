/******************************************************************************\
* File: GLMath.cpp
*
* Author: Josh Taylor
*
* Header: GLMath.h
*
* Description: Provides funtions for use with GLMath's Classes
\******************************************************************************/

#include <cmath>
#include "Util/GLMath.h"

//==============================================================================
// Matrix types
//==============================================================================

//==============================================================================
// Constructs Perspective Matrix
//==============================================================================
Matrix4f GLMath::getPerspective(float fov, float height, float width, float zNear, float zFar) {

	Matrix4f result;

	float aspectRatio = width / height;
	float S = (float)(1 / tan(fov * 0.5f * PI_F / 180.0f));

	result.m11 = S / aspectRatio;
	result.m22 = S;
	result.m33 = -((zFar + zNear) / (zFar - zNear));
	result.m43 = -1;
	result.m34 = -((2 * zFar * zNear) / (zFar - zNear));
	result.m44 = 0;

	return result;
}

//==============================================================================
// Constructs Orthographic Matrix
//==============================================================================
Matrix4f GLMath::getOrthographic(float height, float width, float zNear, float zFar, float scalingFactor) {
	
	Matrix4f result;

	result.m11 = (scalingFactor * 2) / width;
	result.m22 = (scalingFactor * 2) / height;
	result.m33 = -2 / (zFar - zNear);
	result.m34 = -(zFar + zNear) / (zFar - zNear);

	return result;
}

//==============================================================================
// Constructs Transformation Matrix from 
//==============================================================================
Matrix3f GLMath::getTransform2D(float height, float width) {

	Matrix3f result;

	result.m11 = 2 / width;			result.m13 = -1;
	result.m22 = -2 / height;		result.m23 = 1;

	return result;
}

//==============================================================================
// Constructs a Translation Matrix
//==============================================================================
Matrix4f GLMath::getTranslation(float x, float y, float z) {

	Matrix4f result;

	result.m14 = x;
	result.m24 = y;
	result.m34 = z;

	return result;
}

Matrix4f GLMath::getTranslation(Vector3f vec) {
	return getTranslation(vec.x, vec.y, vec.z);
}

//==============================================================================
// Constructs a Scaling Matrix
//==============================================================================
Matrix4f GLMath::getScale(float x, float y, float z) {
	
	Matrix4f result;

	result.m11 = x;
	result.m22 = y;
	result.m33 = z;

	return result;
}

Matrix4f GLMath::getScale(Vector3f vec) {
	return getScale(vec.x, vec.y, vec.z);
}

//==============================================================================
// Constructs a Rotation Matrix
//==============================================================================
Matrix4f GLMath::getRotation(float x, float y, float z) {
	
	Matrix4f result;

	if (x != 0) {
		// Convert to radians
		x *= (float)(PI_F / 180.0f);

		Matrix4f m;

		m.m22 = cos(x);
		m.m32 = sin(x);
		m.m23 = -sin(x);
		m.m33 = cos(x);

		result = result * m;
	}
	if (z != 0) {
		// Convert to radians
		z *= (float)(PI_F / 180.0f);

		Matrix4f m;

		m.m11 = cos(z);
		m.m21 = sin(z);
		m.m12 = -sin(z);
		m.m22 = cos(z);

		result = result * m;
	}
	if (y != 0) {
		// Convert to radians
		y *= (float)(PI_F / 180.0f);

		Matrix4f m;

		m.m11 = cos(y);
		m.m31 = -sin(y);
		m.m13 = sin(y);
		m.m33 = cos(y);

		result = result * m;
	}
	return result;
}

Matrix4f GLMath::getRotation(Vector3f vec) {
	return getRotation(vec.x, vec.y, vec.z);
}

//==============================================================================
// Useful Math Equations
//==============================================================================

//==============================================================================
// Point to Point formulas
//==============================================================================
bool GLMath::distThreshold2f(Vector2f p1, Vector2f p2, float threshold) {
	return distSquared2f(p1, p2) < (threshold * threshold);
}

float GLMath::distSquared2f(Vector2f p1, Vector2f p2) {
	return Vector2f::dot(p2 - p1, p2 - p1);
}

float GLMath::dist2f(Vector2f p1, Vector2f p2) {
	return sqrtf(distSquared2f(p1, p2));
}

//==============================================================================
// Point to Line Segment formulas
//==============================================================================
bool GLMath::distThreshold2f(Vector2f p, LineSeg2f l, float threshold) {
	return distSquared2f(p, l) <= (threshold * threshold);
}

float GLMath::distSquared2f(Vector2f p, LineSeg2f l) {
	float l2 = distSquared2f(l.p1, l.p2);

	if(l2 == 0) return distSquared2f(p, l.p1);

	float t = Vector2f::dot(p - l.p1, l.p2 - l.p1) / l2;

	if(t < 0) return distSquared2f(p, l.p1);

	if(t > 1) return distSquared2f(p, l.p2);

	return distSquared2f(p, l.p1 + ((l.p2 - l.p1) * t));
}

float GLMath::dist2f(Vector2f p, LineSeg2f l) {
	return sqrtf(distSquared2f(p, l));
}

//==============================================================================
// Point Rect intersection
//==============================================================================
bool GLMath::intersect(Vector2f p, Rect r) {
	return p.x >= r.p1.x && p.x <= r.p2.x && p.y >= r.p1.y && p.y <= r.p2.y;
}

//==============================================================================
// Rect Rect intersection
//==============================================================================
bool GLMath::intersect(Rect r1, Rect r2) {
	return	intersect(r1.p1, r2) &&
			intersect(Vector2f(r1.p1.x, r1.p2.y), r2) &&
			intersect(Vector2f(r1.p2.x, r1.p1.y), r2) &&
			intersect(r1.p2, r2);
}

//==============================================================================
// Point Circle intersection
//==============================================================================
bool GLMath::intersect(Vector2f p, Circle c) {
	return distThreshold2f(p, c.center, c.radius);
}

//==============================================================================
// Circle Rect intersection
//==============================================================================
bool GLMath::intersect(Circle c, Rect r) {
	return	intersect(c.center, r) ||
			distThreshold2f(c.center, LineSeg2f(r.p1, Vector2f(r.p2.x, r.p1.y)), c.radius) ||
			distThreshold2f(c.center, LineSeg2f(r.p1, Vector2f(r.p1.x, r.p2.y)), c.radius) ||
			distThreshold2f(c.center, LineSeg2f(Vector2f(r.p1.x, r.p2.y), r.p2), c.radius) ||
			distThreshold2f(c.center, LineSeg2f(Vector2f(r.p2.x, r.p1.y), r.p2), c.radius);
}

//==============================================================================
// Circle Circle intersection
//==============================================================================
bool GLMath::intersect(Circle c1, Circle c2) {
	return distThreshold2f(c1.center, c2.center, c1.radius + c2.radius);
}