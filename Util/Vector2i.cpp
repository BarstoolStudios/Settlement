#include <GL/glew.h>
#include <string>
#include "Util/GLMath.h"

//==============================================================================
// Constructors
//==============================================================================
Vector2i::Vector2i() {
	x = 0;
	y = 0;
}

Vector2i::Vector2i(const Vector2i& vec) {
	x = vec.x;
	y = vec.y;
}

Vector2i::Vector2i(GLint a, GLint b) {
	x = a;
	y = b;
}

//==============================================================================
// Pushes Vector's floats onto floats in order <x, y>
//==============================================================================
void Vector2i::pushOn(std::vector<GLint>* ints) {
	ints->push_back(x);
	ints->push_back(y);
}

//==============================================================================
// Overloaded Operators for Vector on Vector Operations. * is piecewise
//==============================================================================
Vector2i Vector2i::operator + (const Vector2i& vec) {
	Vector2i temp;
	temp.x = x + vec.x;
	temp.y = y + vec.y;
	return temp;
}

Vector2i Vector2i::operator - (const Vector2i& vec) {
	Vector2i temp;
	temp.x = x - vec.x;
	temp.y = y - vec.y;
	return temp;
}

Vector2i Vector2i::operator * (const Vector2i& vec) {
	Vector2i temp;
	temp.x = x * vec.x;
	temp.y = y * vec.y;
	return temp;
}

Vector2i Vector2i::operator / (const Vector2i& vec) {
	Vector2i temp;
	temp.x = x / vec.x;
	temp.y = y / vec.y;
	return temp;
}

Vector2i Vector2i::operator += (const Vector2i& vec) {
	x += vec.x;
	y += vec.y;
	return *this;
}

Vector2i Vector2i::operator -= (const Vector2i& vec) {
	x -= vec.x;
	y -= vec.y;
	return *this;
}

Vector2i Vector2i::operator *= (const Vector2i& vec) {
	x *= vec.x;
	y *= vec.y;
	return *this;
}

Vector2i Vector2i::operator /= (const Vector2i& vec) {
	x /= vec.x;
	y /= vec.y;
	return *this;
}

Vector2i Vector2i::operator + (int n) {
	Vector2i temp;
	temp.x = x + n;
	temp.y = y + n;
	return temp;
}

Vector2i Vector2i::operator - (int n) {
	Vector2i temp;
	temp.x = x - n;
	temp.y = y - n;
	return temp;
}

Vector2i Vector2i::operator * (int n) {
	Vector2i temp;
	temp.x = x * n;
	temp.y = y * n;
	return temp;
}

Vector2i Vector2i::operator / (int n) {
	Vector2i temp;
	temp.x = x / n;
	temp.y = y / n;
	return temp;
}

Vector2i Vector2i::operator += (int n) {
	x += n;
	y += n;
	return *this;
}

Vector2i Vector2i::operator -= (int n) {
	x -= n;
	y -= n;
	return *this;
}

Vector2i Vector2i::operator *= (int n) {
	x *= n;
	y *= n;
	return *this;
}

Vector2i Vector2i::operator /= (int n) {
	x /= n;
	y /= n;
	return *this;
}

bool Vector2i::operator == (const Vector2i& vec) {
	return x == vec.x && y == vec.y;
}

bool Vector2i::operator != (const Vector2i& vec) {
	return x != vec.x || y != vec.y;
}

//==============================================================================
// Returns string Representation of Vector
//==============================================================================
std::string Vector2i::toString() {
	return std::string("(") + std::to_string(x) + ", " + std::to_string(y) + ")";
}

//==============================================================================
// Returns v1 dot v2
//==============================================================================
GLint Vector2i::dot(const Vector2i& v1, const Vector2i& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y);
}

//==============================================================================
// Overloads << for Streams
//==============================================================================
std::ostream& operator<<(std::ostream &strm, const Vector2i& vec) {
	return strm << '(' << vec.x << ", " << vec.y << ')';
}