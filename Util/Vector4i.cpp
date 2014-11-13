#include "Util/GLMath.h"
#include <string>

//==============================================================================
// Constructors
//==============================================================================
Vector4i::Vector4i() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4i::Vector4i(const Vector4i& vec) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
}

Vector4i::Vector4i(GLint a, GLint b, GLint c, GLint d) {
	x = a;
	y = b;
	z = c;
	w = d;
}

//==============================================================================
// Pushes Vector's floats onto floats in order <x, y, z, w>
//==============================================================================
void Vector4i::pushOn(std::vector<GLint>* ints) {
	ints->push_back(x);
	ints->push_back(y);
	ints->push_back(z);
	ints->push_back(w);
}

//==============================================================================
// Overloaded Operators for Vector on Vector Operations. * is piecewise
//==============================================================================
Vector4i Vector4i::operator + (const Vector4i& vec) {
	Vector4i temp;
	temp.x = x + vec.x;
	temp.y = y + vec.y;
	temp.z = z + vec.z;
	temp.w = w + vec.w;
	return temp;
}

Vector4i Vector4i::operator - (const Vector4i& vec) {
	Vector4i temp;
	temp.x = x - vec.x;
	temp.y = y - vec.y;
	temp.z = z - vec.z;
	temp.w = w - vec.w;
	return temp;
}

Vector4i Vector4i::operator * (const Vector4i& vec) {
	Vector4i temp;
	temp.x = x * vec.x;
	temp.y = y * vec.y;
	temp.z = z * vec.z;
	temp.w = w * vec.w;
	return temp;
}

Vector4i Vector4i::operator / (const Vector4i& vec) {
	Vector4i temp;
	temp.x = x / vec.x;
	temp.y = y / vec.y;
	temp.z = z / vec.z;
	temp.w = w / vec.w;
	return temp;
}

Vector4i Vector4i::operator += (const Vector4i& vec) {
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;
	return *this;
}

Vector4i Vector4i::operator -= (const Vector4i& vec) {
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	w -= vec.w;
	return *this;
}

Vector4i Vector4i::operator *= (const Vector4i& vec) {
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	w *= vec.w;
	return *this;
}

Vector4i Vector4i::operator /= (const Vector4i& vec) {
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;
	w /= vec.w;
	return *this;
}

Vector4i Vector4i::operator + (int n) {
	Vector4i temp;
	temp.x = x + n;
	temp.y = y + n;
	temp.z = z + n;
	temp.w = w + n;
	return temp;
}

Vector4i Vector4i::operator - (int n) {
	Vector4i temp;
	temp.x = x - n;
	temp.y = y - n;
	temp.z = z - n;
	temp.w = w - n;
	return temp;
}

Vector4i Vector4i::operator * (int n) {
	Vector4i temp;
	temp.x = x * n;
	temp.y = y * n;
	temp.z = z * n;
	temp.w = w * n;
	return temp;
}

Vector4i Vector4i::operator / (int n) {
	Vector4i temp;
	temp.x = x / n;
	temp.y = y / n;
	temp.z = z / n;
	temp.w = w / n;
	return temp;
}

Vector4i Vector4i::operator += (int n) {
	x += n;
	y += n;
	z += n;
	w += n;
	return *this;
}

Vector4i Vector4i::operator -= (int n) {
	x -= n;
	y -= n;
	z -= n;
	w -= n;
	return *this;
}

Vector4i Vector4i::operator *= (int n) {
	x *= n;
	y *= n;
	z *= n;
	w *= n;
	return *this;
}

Vector4i Vector4i::operator /= (int n) {
	x /= n;
	y /= n;
	z /= n;
	w /= n;
	return *this;
}

bool Vector4i::operator == (const Vector4i& vec) {
	return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
}

bool Vector4i::operator != (const Vector4i& vec) {
	return x != vec.x || y != vec.y || z != vec.z || w != vec.w;
}

//==============================================================================
// Returns string Representation of Vector
//==============================================================================
std::string Vector4i::toString() {
	return std::string("(") + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
}

//==============================================================================
// Returns v1 dot v2
//==============================================================================
GLint Vector4i::dot(const Vector4i& v1, const Vector4i& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

std::ostream& operator<<(std::ostream &strm, const Vector4i& vec) {
	return strm << '(' << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
}