#define _USE_MATH_DEFINES
#include <cmath>
#include "GLMath.h"

Matrix4f GLMath::getPerspective(float fov, float height, float width, float zNear, float zFar) {

	Matrix4f result;

	float aspectRatio = width / height;
	float S = (float)(1 / tan(fov * 0.5f * M_PI / 180.0f));

	result.m00 = S / aspectRatio;
	result.m11 = S;
	result.m22 = -((zFar + zNear) / (zFar - zNear));
	result.m23 = -1;
	result.m32 = -((2 * zFar * zNear) / (zFar - zNear));
	result.m33 = 0;

	return result;
}

Matrix4f GLMath::getOrthographic(float height, float width, float zNear, float zFar, float scalingFactor) {
	
	Matrix4f result;

	result.m00 = (scalingFactor * 2) / width;
	result.m11 = (scalingFactor * 2) / height;
	result.m22 = -2 / (zFar - zNear);
	result.m32 = -(zFar + zNear) / (zFar - zNear);

	return result;
}

Matrix3f GLMath::getTransform2D(float height, float width) {

	Matrix3f result;

	result.m00 = 2 / width;							result.m20 = -1;
	result.m11 = -2 / height;		result.m21 = 1;

	return result;
}

Matrix4f GLMath::getTranslation(float x, float y, float z) {

	Matrix4f result;

	result.m30 = x;
	result.m31 = y;
	result.m32 = z;

	return result;
}

Matrix4f GLMath::getScale(float x, float y, float z) {
	
	Matrix4f result;

	result.m00 = x;
	result.m11 = y;
	result.m22 = z;

	return result;
}

Matrix4f GLMath::getRotation(float x, float y, float z) {
	
	Matrix4f result;

	if (x != 0) {
		// Convert to radians
		x *= (float)(M_PI / 180.0f);

		Matrix4f m;

		m.m11 = cos(x);
		m.m12 = sin(x);
		m.m21 = -sin(x);
		m.m22 = cos(x);

		result = result * m;
	}
	if (z != 0) {
		// Convert to radians
		z *= (float)(M_PI / 180.0f);

		Matrix4f m;

		m.m00 = cos(z);
		m.m01 = sin(z);
		m.m10 = -sin(z);
		m.m11 = cos(z);

		result = result * m;
	}
	if (y != 0) {
		// Convert to radians
		y *= (float)(M_PI / 180.0f);

		Matrix4f m;

		m.m00 = cos(y);
		m.m02 = -sin(y);
		m.m20 = sin(y);
		m.m22 = cos(y);

		result = result * m;
	}
	return result;
}

Matrix3f GLMath::fourToThree(const Matrix4f& m4) {
	
	Matrix3f m3;

	m3.m00 = m4.m00;
	m3.m01 = m4.m01;
	m3.m02 = m4.m02;

	m3.m10 = m4.m10;
	m3.m11 = m4.m11;
	m3.m12 = m4.m12;

	m3.m20 = m4.m20;
	m3.m21 = m4.m21;
	m3.m22 = m4.m22;

	return m3;
}