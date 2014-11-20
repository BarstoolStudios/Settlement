#include <GL/glew.h>
#include <string>
#include "Util/GLMath.h"

//==============================================================================
// Constructors
//==============================================================================
Vector2f::Vector2f() {
	x = 0;
	y = 0;
}

Vector2f::Vector2f(const Vector2f& vec) {
	x = vec.x;
	y = vec.y;
}

Vector2f::Vector2f(const Vector2i& vec) {
	x = vec.x;
	y = vec.y;
}

Vector2f::Vector2f(GLfloat a, GLfloat b) {
	x = a;
	y = b;
}

//==============================================================================
// Pushes Vector's floats onto floats in order <x, y>
//==============================================================================
void Vector2f::pushOn(std::vector<GLfloat>* floats) {
	floats->push_back(x);
	floats->push_back(y);
}

//==============================================================================
// Overloaded Operators for Vector on Vector Operations. * is piecewise
//==============================================================================
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

Vector2f Vector2f::operator + (float n) {
	Vector2f temp;
	temp.x = x + n;
	temp.y = y + n;
	return temp;
}

Vector2f Vector2f::operator - (float n) {
	Vector2f temp;
	temp.x = x - n;
	temp.y = y - n;
	return temp;
}

Vector2f Vector2f::operator * (float n) {
	Vector2f temp;
	temp.x = x * n;
	temp.y = y * n;
	return temp;
}

Vector2f Vector2f::operator / (float n) {
	Vector2f temp;
	temp.x = x / n;
	temp.y = y / n;
	return temp;
}

Vector2f Vector2f::operator += (float n) {
	x += n;
	y += n;
	return *this;
}

Vector2f Vector2f::operator -= (float n) {
	x -= n;
	y -= n;
	return *this;
}

Vector2f Vector2f::operator *= (float n) {
	x *= n;
	y *= n;
	return *this;
}

Vector2f Vector2f::operator /= (float n) {
	x /= n;
	y /= n;
	return *this;
}

//==============================================================================
// Returns string Representation of Vector
//==============================================================================
std::string Vector2f::toString() {
	return std::string("(") + std::to_string(x) + ", " + std::to_string(y) +  ")";
}

//==============================================================================
// Returns v1 dot v2
//==============================================================================
GLfloat Vector2f::dot(const Vector2f& v1, const Vector2f& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y);
}

//==============================================================================
// Overloads << for Streams
//==============================================================================
std::ostream& operator<<(std::ostream &strm, const Vector2f& vec) {
	return strm << '(' << vec.x << ", " << vec.y << ')';
}