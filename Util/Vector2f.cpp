#include <GL/glew.h>
#include "Util/GLMath.h"

Vector2f::Vector2f() {
	x = 0;
	y = 0;
}

Vector2f::Vector2f(const Vector2f& vec) {
	x = vec.x;
	y = vec.y;
}

Vector2f::Vector2f(GLfloat a, GLfloat b) {
	x = a;
	y = b;
}

void Vector2f::pushOn(std::vector<GLfloat>* floats) {
	floats->push_back(x);
	floats->push_back(y);
}

Vector2f Vector2f::operator + (const Vector2f& vec) {
	Vector2f temp;
	temp.x = x + vec.x;
	temp.y = y + vec.y;
	return temp;
}

Vector2f Vector2f::operator - (const Vector2f& vec) {
	Vector2f temp;
	temp.x = x - vec.x;
	temp.y = y - vec.y;
	return temp;
}

Vector2f Vector2f::operator * (const Vector2f& vec) {
	Vector2f temp;
	temp.x = x * vec.x;
	temp.y = y * vec.y;
	return temp;
}

Vector2f Vector2f::operator / (const Vector2f& vec) {
	Vector2f temp;
	temp.x = x / vec.x;
	temp.y = y / vec.y;
	return temp;
}

Vector2f Vector2f::operator += (const Vector2f& vec) {
	x += vec.x;
	y += vec.y;
	return *this;
}

Vector2f Vector2f::operator -= (const Vector2f& vec) {
	x -= vec.x;
	y -= vec.y;
	return *this;
}

Vector2f Vector2f::operator *= (const Vector2f& vec) {
	x *= vec.x;
	y *= vec.y;
	return *this;
}

Vector2f Vector2f::operator /= (const Vector2f& vec) {
	x /= vec.x;
	y /= vec.y;
	return *this;
}

GLfloat Vector2f::dot(const Vector2f& v1, const Vector2f& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y);
}

std::ostream& operator<<(std::ostream &strm, const Vector2f& vec) {
	return strm << '(' << vec.x << ", " << vec.y << ")";
}