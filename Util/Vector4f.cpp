#include "Util/GLMath.h"
#include <string>

//==============================================================================
// Constructors
//==============================================================================
Vector4f::Vector4f() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4f::Vector4f(const Vector4f& vec) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
}

Vector4f::Vector4f(const Vector4i& vec) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
}

Vector4f::Vector4f(GLfloat a, GLfloat b, GLfloat c, GLfloat d) {
	x = a;
	y = b;
	z = c;
	w = d;
}

//==============================================================================
// Pushes Vector's floats onto floats in order <x, y, z, w>
//==============================================================================
void Vector4f::pushOn(std::vector<GLfloat>* floats) {
	floats->push_back(x);
	floats->push_back(y);
	floats->push_back(z);
	floats->push_back(w);
}

//==============================================================================
// Overloaded Operators for Vector on Vector Operations. * is piecewise
//==============================================================================
Vector4f Vector4f::operator + (const Vector4f& vec) {
	Vector4f temp;
	temp.x = x + vec.x;
	temp.y = y + vec.y;
	temp.z = z + vec.z;
	temp.w = w + vec.w;
	return temp;
}

Vector4f Vector4f::operator - (const Vector4f& vec) {
	Vector4f temp;
	temp.x = x - vec.x;
	temp.y = y - vec.y;
	temp.z = z - vec.z;
	temp.w = w - vec.w;
	return temp;
}

Vector4f Vector4f::operator * (const Vector4f& vec) {
	Vector4f temp;
	temp.x = x * vec.x;
	temp.y = y * vec.y;
	temp.z = z * vec.z;
	temp.w = w * vec.w;
	return temp;
}

Vector4f Vector4f::operator / (const Vector4f& vec) {
	Vector4f temp;
	temp.x = x / vec.x;
	temp.y = y / vec.y;
	temp.z = z / vec.z;
	temp.w = w / vec.w;
	return temp;
}

Vector4f Vector4f::operator += (const Vector4f& vec) {
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;
	return *this;
}

Vector4f Vector4f::operator -= (const Vector4f& vec) {
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	w -= vec.w;
	return *this;
}

Vector4f Vector4f::operator *= (const Vector4f& vec) {
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	w *= vec.w;
	return *this;
}

Vector4f Vector4f::operator /= (const Vector4f& vec) {
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;
	w /= vec.w;
	return *this;
}

Vector4f Vector4f::operator + (float n) {
	Vector4f temp;
	temp.x = x + n;
	temp.y = y + n;
	temp.z = z + n;
	temp.w = w + n;
	return temp;
}

Vector4f Vector4f::operator - (float n) {
	Vector4f temp;
	temp.x = x - n;
	temp.y = y - n;
	temp.z = z - n;
	temp.w = w - n;
	return temp;
}

Vector4f Vector4f::operator * (float n) {
	Vector4f temp;
	temp.x = x * n;
	temp.y = y * n;
	temp.z = z * n;
	temp.w = w * n;
	return temp;
}

Vector4f Vector4f::operator / (float n) {
	Vector4f temp;
	temp.x = x / n;
	temp.y = y / n;
	temp.z = z / n;
	temp.w = w / n;
	return temp;
}

Vector4f Vector4f::operator += (float n) {
	x += n;
	y += n;
	z += n;
	w += n;
	return *this;
}

Vector4f Vector4f::operator -= (float n) {
	x -= n;
	y -= n;
	z -= n;
	w -= n;
	return *this;
}

Vector4f Vector4f::operator *= (float n) {
	x *= n;
	y *= n;
	z *= n;
	w *= n;
	return *this;
}

Vector4f Vector4f::operator /= (float n) {
	x /= n;
	y /= n;
	z /= n;
	w /= n;
	return *this;
}

//==============================================================================
// Returns string Representation of Vector
//==============================================================================
std::string Vector4f::toString() {
	return std::string("(") + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
}

//==============================================================================
// Returns v1 dot v2
//==============================================================================
GLfloat Vector4f::dot(const Vector4f& v1, const Vector4f& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

std::ostream& operator<<(std::ostream &strm, const Vector4f& vec) {
	return strm << '(' << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
}