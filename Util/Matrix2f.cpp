/******************************************************************************\
* File: Matrix2f.cpp
*
* Author: Josh Taylor
*
* Header: GLMath.h
*
* Description: A 2x2 Matrix Class with float members. Used for graphics
*              calculations. Follows matrix convention m<row><column>
\******************************************************************************/

#include "Util/GLMath.h"

//==============================================================================
// Constructors
//==============================================================================
Matrix2f::Matrix2f() {
	m11 = 0; m12 = 0;
	m21 = 0; m22 = 0;
}

Matrix2f::Matrix2f(
	GLfloat m00, GLfloat m10,
	GLfloat m01, GLfloat m11)
	:
	m11(m11), m12(m12),
	m21(m21), m22(m22)
	{}

Matrix2f::Matrix2f(Matrix2f& mat) {
	m11 = mat.m11; m12 = mat.m12;
	m21 = mat.m21; m22 = mat.m22;
}

//==============================================================================
// Returns Matrix as Array (Row-Major)
//==============================================================================
void Matrix2f::asArray(GLfloat* arr) {
	arr[0] = m11; arr[1] = m12;
	arr[2] = m21; arr[3] = m22;
}

//==============================================================================
// Takes Transpose of Current Matrix (In Place)
//==============================================================================
void Matrix2f::transpose() {
	Matrix2f temp(*this);

	m21 = temp.m12;
	m12 = temp.m21;
}

//==============================================================================
// Takes Inverse of Current Matrix (In Place)
//==============================================================================
void Matrix2f::inverse() {

	GLfloat a = m11;
	GLfloat d = m22;

	GLfloat invDet = 1.0f / determinant();

	m11 = d * invDet;
	m22 = a * invDet;

	m12 *= -invDet;
	m21 *= -invDet;
}

//==============================================================================
// Returns Determinate of Current Matrix
//==============================================================================
GLfloat Matrix2f::determinant() {
	return (m11 * m22) - (m12 * m21);
}

//==============================================================================
// Matrix Matrix Multiplication
//==============================================================================
Matrix2f Matrix2f::operator * (const Matrix2f& m) {
	Matrix2f temp;

	Vector2f c0(m.m11, m.m21);
	Vector2f c1(m.m12, m.m22);

	Vector2f r0(m11, m12);
	Vector2f r1(m21, m22);

	temp.m11 = Vector2f::dot(c0, r0);
	temp.m21 = Vector2f::dot(c0, r1);

	temp.m12 = Vector2f::dot(c1, r0);
	temp.m22 = Vector2f::dot(c1, r1);

	return temp;
}

//==============================================================================
// Matrix Vector Multiplication
//==============================================================================
Vector2f Matrix2f::operator * (const Vector2f& v) {
	Vector2f temp;

	Vector2f r0(m11, m12);
	Vector2f r1(m21, m22);

	temp.x = Vector2f::dot(v, r0);
	temp.y = Vector2f::dot(v, r1);

	return temp;
}

//==============================================================================
// Overloads << for Streams
//==============================================================================
std::ostream& operator<<(std::ostream &strm, const Matrix2f& mat) {
	return strm << mat.m11 << ' ' << mat.m12 << '\n'
				<< mat.m21 << ' ' << mat.m22 << '\n';
}