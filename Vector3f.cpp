#include <GL\glew.h>
#include <cmath>
#include "GLMath.h"

Vector3f::Vector3f() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3f::Vector3f(const Vector3f& vec) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

Vector3f::Vector3f(GLfloat a, GLfloat b, GLfloat c) {
	x = a;
	y = b;
	z = c;
}

void Vector3f::pushOn(std::vector<GLfloat>* floats) {
	floats->push_back(x);
	floats->push_back(y);
	floats->push_back(z);
}

Vector3f Vector3f::operator + (const Vector3f& vec) {
	Vector3f temp;
	temp.x = x + vec.x;
	temp.y = y + vec.y;
	temp.z = z + vec.z;
	return temp;
}

Vector3f Vector3f::operator - (const Vector3f& vec) {
	Vector3f temp;
	temp.x = x - vec.x;
	temp.y = y - vec.y;
	temp.z = z - vec.z;
	return temp;
}

Vector3f Vector3f::operator * (const Vector3f& vec) {
	Vector3f temp;
	temp.x = x * vec.x;
	temp.y = y * vec.y;
	temp.z = z * vec.z;
	return temp;
}

Vector3f Vector3f::operator / (const Vector3f& vec) {
	Vector3f temp;
	temp.x = x / vec.x;
	temp.y = y / vec.y;
	temp.z = z / vec.z;
	return temp;
}

Vector3f Vector3f::operator += (const Vector3f& vec) {
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

Vector3f Vector3f::operator -= (const Vector3f& vec) {
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

Vector3f Vector3f::operator *= (const Vector3f& vec) {
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	return *this;
}

Vector3f Vector3f::operator /= (const Vector3f& vec) {
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;
	return *this;
}

GLfloat Vector3f::dot(const Vector3f& v1, const Vector3f& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Vector3f Vector3f::cross(const Vector3f& v1, const Vector3f& v2) {
	Vector3f result;

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);

	return result;
}

Vector3f Vector3f::norm(const Vector3f& vec) {
	GLfloat len = std::sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	return Vector3f(vec.x / len, vec.y / len, vec.z / len);
}

std::ostream& operator<<(std::ostream &strm, const Vector3f& vec) {
	return strm << '(' << vec.x << ", " << vec.y << ", " << vec.z << ")\n";
}