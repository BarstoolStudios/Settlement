#include "Util/GLMath.h"

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

Vector4f::Vector4f(GLfloat a, GLfloat b, GLfloat c, GLfloat d) {
	x = a;
	y = b;
	z = c;
	w = d;
}

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

GLfloat Vector4f::dot(const Vector4f& v1, const Vector4f& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

std::ostream& operator<<(std::ostream &strm, const Vector4f& vec) {
	return strm << '(' << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")\n";
}