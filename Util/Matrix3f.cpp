/******************************************************************************\
* File: Matrix3f.cpp
*
* Author: Josh Taylor
*
* Header: GLMath.h
*
* Description: A 3x3 Matrix Class with float members. Used for graphics
*              calculations. Follows matrix convention m<row><column>
\******************************************************************************/

#include "Util/GLMath.h"

//==============================================================================
// Constructors
//==============================================================================
Matrix3f::Matrix3f() {
	m11 = 1; m12 = 0; m13 = 0;
	m21 = 0; m22 = 1; m23 = 0;
	m31 = 0; m32 = 0; m33 = 1;
}

Matrix3f::Matrix3f(Matrix3f& mat) {
	m11 = mat.m11; m12 = mat.m12; m13 = mat.m13;
	m21 = mat.m21; m22 = mat.m22; m23 = mat.m23;
	m31 = mat.m31; m32 = mat.m32; m33 = mat.m33;
}

Matrix3f::Matrix3f(Matrix4f& mat) {
	m11 = mat.m11; m12 = mat.m12; m13 = mat.m13;
	m21 = mat.m21; m22 = mat.m22; m23 = mat.m23;
	m31 = mat.m31; m32 = mat.m32; m33 = mat.m33;
}

Matrix3f::Matrix3f(
	GLfloat m11, GLfloat m12, GLfloat m13,
	GLfloat m21, GLfloat m22, GLfloat m23,
	GLfloat m31, GLfloat m32, GLfloat m33)
	:
	m11(m11), m12(m12), m13(m13),
	m21(m21), m22(m22), m23(m23),
	m31(m31), m32(m32), m33(m33)
	{}

//==============================================================================
// Returns Matrix as Array (Row-Major)
//==============================================================================
void Matrix3f::asArray(GLfloat* arr) {
	arr[0] = m11; arr[1] = m12; arr[2] = m13;
	arr[3] = m21; arr[4] = m22; arr[5] = m23;
	arr[6] = m31; arr[7] = m32; arr[8] = m33;
}

//==============================================================================
// Takes Transpose of Current Matrix (In Place)
//==============================================================================
void Matrix3f::transpose() {
	Matrix3f temp(*this);

	m21 = temp.m12;
	m31 = temp.m13;

	m12 = temp.m21;
	m32 = temp.m23;

	m13 = temp.m31;
	m23 = temp.m32;

}

//==============================================================================
// Takes Inverse of Current Matrix (In Place)
//==============================================================================
void Matrix3f::inverse() {
	// Find Inverse Determinant
	GLfloat invDet = 1.0f / determinant();

	// Find Cofactors
	GLfloat c11 = Matrix2f(m22, m23, m32, m33).determinant();
	GLfloat c21 = -Matrix2f(m12, m13, m32, m33).determinant();
	GLfloat c31 = Matrix2f(m12, m13, m22, m23).determinant();

	GLfloat c12 = -Matrix2f(m21, m23, m31, m33).determinant();
	GLfloat c22 = Matrix2f(m11, m13, m31, m33).determinant();
	GLfloat c32 = -Matrix2f(m11, m13, m21, m23).determinant();

	GLfloat c13 = Matrix2f(m21, m22, m31, m32).determinant();
	GLfloat c23 = -Matrix2f(m11, m12, m31, m32).determinant();
	GLfloat c33 = Matrix2f(m11, m12, m21, m22).determinant();

	// Take Transpose of Cofactor Matrix and Multiply by Inverse Determinant
	m11 = c11 * invDet;
	m21 = c12 * invDet;
	m31 = c13 * invDet;

	m12 = c21 * invDet;
	m22 = c22 * invDet;
	m32 = c23 * invDet;

	m13 = c31 * invDet;
	m23 = c32 * invDet;
	m33 = c33 * invDet;
}

//==============================================================================
// Returns Determinate of Current Matrix
//==============================================================================
GLfloat Matrix3f::determinant() {
	
	return	 m11 * Matrix2f(m22, m23, m32, m33).determinant()
		   - m21 * Matrix2f(m12, m13, m32, m33).determinant()
		   + m31 * Matrix2f(m12, m13, m22, m23).determinant();

}

//==============================================================================
// Matrix Matrix Multiplication
//==============================================================================
Matrix3f Matrix3f::operator * (const Matrix3f& m) {
	Matrix3f temp;

	Vector3f c0(m.m11, m.m21, m.m31);
	Vector3f c1(m.m12, m.m22, m.m32);
	Vector3f c2(m.m13, m.m23, m.m33);

	Vector3f r0(m11, m12, m13);
	Vector3f r1(m21, m22, m23);
	Vector3f r2(m31, m32, m33);

	temp.m11 = Vector3f::dot(c0, r0);
	temp.m21 = Vector3f::dot(c0, r1);
	temp.m31 = Vector3f::dot(c0, r2);

	temp.m12 = Vector3f::dot(c1, r0);
	temp.m22 = Vector3f::dot(c1, r1);
	temp.m32 = Vector3f::dot(c1, r2);

	temp.m13 = Vector3f::dot(c2, r0);
	temp.m23 = Vector3f::dot(c2, r1);
	temp.m33 = Vector3f::dot(c2, r2);

	return temp;
}

//==============================================================================
// Matrix Vector Multiplication
//==============================================================================
Vector3f Matrix3f::operator * (const Vector3f& v) {
	Vector3f temp;

	Vector3f r0(m11, m12, m13);
	Vector3f r1(m21, m22, m23);
	Vector3f r2(m31, m32, m33);

	temp.x = Vector3f::dot(v, r0);
	temp.y = Vector3f::dot(v, r1);
	temp.z = Vector3f::dot(v, r2);

	return temp;
}

//==============================================================================
// Overloads << for Streams
//==============================================================================
std::ostream& operator<<(std::ostream &strm, const Matrix3f& mat) {
	return strm << mat.m11 << ' ' << mat.m12 << ' ' << mat.m13 << '\n'
				<< mat.m21 << ' ' << mat.m22 << ' ' << mat.m23 << '\n'
				<< mat.m31 << ' ' << mat.m32 << ' ' << mat.m33 << '\n';
}