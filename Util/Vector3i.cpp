#include <GL/glew.h>
#include <cmath>
#include <string>
#include "Util/GLMath.h"

Vector3i::Vector3i() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3i::Vector3i(const Vector3i& vec) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

Vector3i::Vector3i(GLint a, GLint b, GLint c) {
	x = a;
	y = b;
	z = c;
}

//==============================================================================
// Pushes Vector's floats onto floats in order <x, y, z>
//==============================================================================
void Vector3i::pushOn(std::vector<GLint>* ints) {
	ints->push_back(x);
	ints->push_back(y);
	ints->push_back(z);
}

//==============================================================================
// Overloaded Operators for Vector on Vector Operations. * is piecewise
//==============================================================================
Vector3i Vector3i::operator + (const Vector3i& vec) {
	Vector3i temp;
	temp.x = x + vec.x;
	temp.y = y + vec.y;
	temp.z = z + vec.z;
	return temp;
}

Vector3i Vector3i::operator - (const Vector3i& vec) {
	Vector3i temp;
	temp.x = x - vec.x;
	temp.y = y - vec.y;
	temp.z = z - vec.z;
	return temp;
}

Vector3i Vector3i::operator * (const Vector3i& vec) {
	Vector3i temp;
	temp.x = x * vec.x;
	temp.y = y * vec.y;
	temp.z = z * vec.z;
	return temp;
}

Vector3i Vector3i::operator / (const Vector3i& vec) {
	Vector3i temp;
	temp.x = x / vec.x;
	temp.y = y / vec.y;
	temp.z = z / vec.z;
	return temp;
}

Vector3i Vector3i::operator += (const Vector3i& vec) {
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

Vector3i Vector3i::operator -= (const Vector3i& vec) {
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

Vector3i Vector3i::operator *= (const Vector3i& vec) {
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	return *this;
}

Vector3i Vector3i::operator /= (const Vector3i& vec) {
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;
	return *this;
}

Vector3i Vector3i::operator + (int n) {
	Vector3i temp;
	temp.x = x + n;
	temp.y = y + n;
	temp.z = z + n;
	return temp;
}

Vector3i Vector3i::operator - (int n) {
	Vector3i temp;
	temp.x = x - n;
	temp.y = y - n;
	temp.z = z - n;
	return temp;
}

Vector3i Vector3i::operator * (int n) {
	Vector3i temp;
	temp.x = x * n;
	temp.y = y * n;
	temp.z = z * n;
	return temp;
}

Vector3i Vector3i::operator / (int n) {
	Vector3i temp;
	temp.x = x / n;
	temp.y = y / n;
	temp.z = z / n;
	return temp;
}

Vector3i Vector3i::operator += (int n) {
	x += n;
	y += n;
	z += n;
	return *this;
}

Vector3i Vector3i::operator -= (int n) {
	x -= n;
	y -= n;
	z -= n;
	return *this;
}

Vector3i Vector3i::operator *= (int n) {
	x *= n;
	y *= n;
	z *= n;
	return *this;
}

Vector3i Vector3i::operator /= (int n) {
	x /= n;
	y /= n;
	z /= n;
	return *this;
}

bool Vector3i::operator == (const Vector3i& vec) {
	return x == vec.x && y == vec.y && z == vec.z;
}

bool Vector3i::operator != (const Vector3i& vec) {
	return x != vec.x || y != vec.y || z != vec.z;
}

//==============================================================================
// Returns string Representation of Vector
//==============================================================================
std::string Vector3i::toString() {
	return std::string("(") + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

//================================s==============================================
// Returns v1 dot v2
//==============================================================================
GLint Vector3i::dot(const Vector3i& v1, const Vector3i& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

//==============================================================================
// Returns v1 cross v2
//==============================================================================
Vector3i Vector3i::cross(const Vector3i& v1, const Vector3i& v2) {
	Vector3i result;

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);

	return result;
}

//==============================================================================
// Overloads << for Streams
//==============================================================================
std::ostream& operator<<(std::ostream &strm, const Vector3i& vec) {
	return strm << '(' << vec.x << ", " << vec.y << ", " << vec.z << ")";
}