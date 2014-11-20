#include <GL/glew.h>
#include <cmath>
#include <string>
#include "Util/GLMath.h"

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

Vector3f::Vector3f(const Vector3i& vec) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

Vector3f::Vector3f(GLfloat a, GLfloat b, GLfloat c) {
	x = a;
	y = b;
	z = c;
}

//==============================================================================
// Pushes Vector's floats onto floats in order <x, y, z>
//==============================================================================
void Vector3f::pushOn(std::vector<GLfloat>* floats) {
	floats->push_back(x);
	floats->push_back(y);
	floats->push_back(z);
}

//==============================================================================
// Overloaded Operators for Vector on Vector Operations. * is piecewise
//==============================================================================
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

Vector3f Vector3f::operator + (float n) {
	Vector3f temp;
	temp.x = x + n;
	temp.y = y + n;
	temp.z = z + n;
	return temp;
}

Vector3f Vector3f::operator - (float n) {
	Vector3f temp;
	temp.x = x - n;
	temp.y = y - n;
	temp.z = z - n;
	return temp;
}

Vector3f Vector3f::operator * (float n) {
	Vector3f temp;
	temp.x = x * n;
	temp.y = y * n;
	temp.z = z * n;
	return temp;
}

Vector3f Vector3f::operator / (float n) {
	Vector3f temp;
	temp.x = x / n;
	temp.y = y / n;
	temp.z = z / n;
	return temp;
}

Vector3f Vector3f::operator += (float n) {
	x += n;
	y += n;
	z += n;
	return *this;
}

Vector3f Vector3f::operator -= (float n) {
	x -= n;
	y -= n;
	z -= n;
	return *this;
}

Vector3f Vector3f::operator *= (float n) {
	x *= n;
	y *= n;
	z *= n;
	return *this;
}

Vector3f Vector3f::operator /= (float n) {
	x /= n;
	y /= n;
	z /= n;
	return *this;
}

//==============================================================================
// Returns string Representation of Vector
//==============================================================================
std::string Vector3f::toString() {
	return std::string("(") + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

//================================s==============================================
// Returns v1 dot v2
//==============================================================================
GLfloat Vector3f::dot(const Vector3f& v1, const Vector3f& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

//==============================================================================
// Returns v1 cross v2
//==============================================================================
Vector3f Vector3f::cross(const Vector3f& v1, const Vector3f& v2) {
	Vector3f result;

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);

	return result;
}

//==============================================================================
// Returns Normalized vec
//==============================================================================
Vector3f Vector3f::norm(const Vector3f& vec) {
	GLfloat len = std::sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	return Vector3f(vec.x / len, vec.y / len, vec.z / len);
}

//==============================================================================
// Overloads << for Streams
//==============================================================================
std::ostream& operator<<(std::ostream &strm, const Vector3f& vec) {
	return strm << '(' << vec.x << ", " << vec.y << ", " << vec.z << ")";
}