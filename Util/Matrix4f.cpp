/******************************************************************************\
* File: Matrix4f.cpp
*
* Author: Josh Taylor
*
* Header: GLMath.h
*
* Description: A 4x4 Matrix Class with float members. Used for graphics
*              calculations. Follows matrix convention m<row><column>
\******************************************************************************/

#include "Util/GLMath.h"

//==============================================================================
// Constructors
//==============================================================================
Matrix4f::Matrix4f() {
	m11 = 1; m12 = 0; m13 = 0; m14 = 0;
	m21 = 0; m22 = 1; m23 = 0; m24 = 0;
	m31 = 0; m32 = 0; m33 = 1; m34 = 0;
	m41 = 0; m42 = 0; m43 = 0; m44 = 1;
}

Matrix4f::Matrix4f(Matrix4f& mat) {
	m11 = mat.m11; m12 = mat.m12; m13 = mat.m13; m14 = mat.m14;
	m21 = mat.m21; m22 = mat.m22; m23 = mat.m23; m24 = mat.m24;
	m31 = mat.m31; m32 = mat.m32; m33 = mat.m33; m34 = mat.m34;
	m41 = mat.m41; m42 = mat.m42; m43 = mat.m43; m44 = mat.m44;
}

Matrix4f::Matrix4f(
	GLfloat m11, GLfloat m12, GLfloat m13, GLfloat m14,
	GLfloat m21, GLfloat m22, GLfloat m23, GLfloat m24,
	GLfloat m31, GLfloat m32, GLfloat m33, GLfloat m34,
	GLfloat m41, GLfloat m42, GLfloat m43, GLfloat m44)
	:
	m11(m11), m12(m12), m13(m13), m14(m14),
	m21(m21), m22(m22), m23(m23), m24(m24),
	m31(m31), m32(m32), m33(m33), m34(m34),
	m41(m41), m42(m42), m43(m43), m44(m44)
	{}

void Matrix4f::pushOn(std::vector<GLfloat>* floats) {
	floats->push_back(m11); floats->push_back(m12); floats->push_back(m13); floats->push_back(m14);
	floats->push_back(m21); floats->push_back(m22); floats->push_back(m23); floats->push_back(m24);
	floats->push_back(m31); floats->push_back(m32); floats->push_back(m33); floats->push_back(m34);
	floats->push_back(m41); floats->push_back(m42); floats->push_back(m43); floats->push_back(m44);

}

//==============================================================================
// Returns Matrix as Array (Row-Major)
//==============================================================================
void Matrix4f::asArray(GLfloat* arr) {
	arr[0] =  m11; arr[1] =  m12; arr[2] =  m13; arr[3] =  m14;
	arr[4] =  m21; arr[5] =  m22; arr[6] =  m23; arr[7] =  m24;
	arr[8] =  m31; arr[9] =  m32; arr[10] = m33; arr[11] = m34;
	arr[12] = m41; arr[13] = m42; arr[14] = m43; arr[15] = m44;
}

//==============================================================================
// Takes Transpose of Current Matrix (In Place)
//==============================================================================
void Matrix4f::transpose() {
	Matrix4f temp(*this);

	m21 = temp.m12;
	m31 = temp.m13;
	m41 = temp.m14;

	m12 = temp.m21;
	m32 = temp.m23;
	m42 = temp.m24;

	m13 = temp.m31;
	m23 = temp.m32;
	m43 = temp.m34;

	m14 = temp.m41;
	m24 = temp.m42;
	m34 = temp.m43;
}

//==============================================================================
// Takes Inverse of Current Matrix (In Place)
//==============================================================================
void Matrix4f::inverse() {
	// Find Inverse Determinant
	GLfloat invDet = 1.0f / determinant();

	// Find Cofactors
	GLfloat c11 = Matrix3f(m22, m23, m24, m32, m33, m34, m42, m43, m44).determinant();
	GLfloat c21 = -Matrix3f(m12, m13, m14, m32, m33, m34, m42, m43, m44).determinant();
	GLfloat c31 = Matrix3f(m12, m13, m14, m22, m23, m24, m42, m43, m44).determinant();
	GLfloat c41 = -Matrix3f(m12, m13, m14, m22, m23, m24, m32, m33, m34).determinant();

	GLfloat c12 = -Matrix3f(m21, m23, m24, m31, m33, m34, m41, m43, m44).determinant();
	GLfloat c22 = Matrix3f(m11, m13, m14, m31, m33, m34, m41, m43, m44).determinant();
	GLfloat c32 = -Matrix3f(m11, m13, m41, m21, m23, m24, m41, m43, m44).determinant();
	GLfloat c42 = Matrix3f(m11, m13, m14, m21, m23, m24, m31, m33, m34).determinant();

	GLfloat c13 = Matrix3f(m21, m22, m24, m31, m32, m34, m41, m42, m44).determinant();
	GLfloat c23 = -Matrix3f(m11, m12, m14, m31, m32, m34, m41, m42, m44).determinant();
	GLfloat c33 = Matrix3f(m11, m12, m14, m21, m22, m24, m41, m42, m44).determinant();
	GLfloat c43 = -Matrix3f(m11, m12, m14, m21, m22, m24, m31, m32, m34).determinant();

	GLfloat c14 = -Matrix3f(m21, m22, m23, m31, m32, m33, m41, m42, m43).determinant();
	GLfloat c24 = Matrix3f(m11, m12, m13, m31, m32, m33, m41, m42, m43).determinant();
	GLfloat c34 = -Matrix3f(m11, m12, m13, m21, m22, m23, m41, m42, m43).determinant();
	GLfloat c44 = Matrix3f(m11, m12, m13, m21, m22, m23, m31, m32, m33).determinant();

	// Take Transpose of Cofactor Matrix and Multiply by Inverse Determinant
	m11 = c11 * invDet;
	m21 = c12 * invDet;
	m31 = c13 * invDet;
	m41 = c14 * invDet;

	m12 = c21 * invDet;
	m22 = c22 * invDet;
	m32 = c23 * invDet;
	m42 = c24 * invDet;

	m13 = c31 * invDet;
	m23 = c32 * invDet;
	m33 = c33 * invDet;
	m43 = c34 * invDet;

	m14 = c41 * invDet;
	m24 = c42 * invDet;
	m34 = c43 * invDet;
	m44 = c44 * invDet;
}

//==============================================================================
// Returns Determinate of Current Matrix
//==============================================================================
GLfloat Matrix4f::determinant() {
	return	 m11 * Matrix3f(m22, m23, m24, m32, m33, m34, m42, m43, m44).determinant()
		   - m21 * Matrix3f(m12, m13, m14, m32, m33, m34, m42, m43, m44).determinant()
		   + m31 * Matrix3f(m12, m13, m14, m22, m23, m24, m42, m43, m44).determinant()
		   - m41 * Matrix3f(m12, m13, m14, m22, m23, m24, m32, m33, m34).determinant();
}

//==============================================================================
// Matrix Matrix Multiplication
//==============================================================================
Matrix4f Matrix4f::operator * (const Matrix4f& m) {
	Matrix4f temp;

	Vector4f c0(m.m11, m.m21, m.m31, m.m41);
	Vector4f c1(m.m12, m.m22, m.m32, m.m42);
	Vector4f c2(m.m13, m.m23, m.m33, m.m43);
	Vector4f c3(m.m14, m.m24, m.m34, m.m44);

	Vector4f r0(m11, m12, m13, m14);
	Vector4f r1(m21, m22, m23, m24);
	Vector4f r2(m31, m32, m33, m34);
	Vector4f r3(m41, m42, m43, m44);

	temp.m11 = Vector4f::dot(c0, r0);
	temp.m21 = Vector4f::dot(c0, r1);
	temp.m31 = Vector4f::dot(c0, r2);
	temp.m41 = Vector4f::dot(c0, r3);

	temp.m12 = Vector4f::dot(c1, r0);
	temp.m22 = Vector4f::dot(c1, r1);
	temp.m32 = Vector4f::dot(c1, r2);
	temp.m42 = Vector4f::dot(c1, r3);

	temp.m13 = Vector4f::dot(c2, r0);
	temp.m23 = Vector4f::dot(c2, r1);
	temp.m33 = Vector4f::dot(c2, r2);
	temp.m43 = Vector4f::dot(c2, r3);

	temp.m14 = Vector4f::dot(c3, r0);
	temp.m24 = Vector4f::dot(c3, r1);
	temp.m34 = Vector4f::dot(c3, r2);
	temp.m44 = Vector4f::dot(c3, r3);

	return temp;
}

//==============================================================================
// Matrix Vector Multiplication
//==============================================================================
Vector4f Matrix4f::operator * (const Vector4f& v) {
	Vector4f temp;

	Vector4f r0(m11, m12, m13, m14);
	Vector4f r1(m21, m22, m23, m24);
	Vector4f r2(m31, m32, m33, m34);
	Vector4f r3(m41, m42, m43, m44);

	temp.x = Vector4f::dot(v, r0);
	temp.y = Vector4f::dot(v, r1);
	temp.z = Vector4f::dot(v, r2);
	temp.w = Vector4f::dot(v, r3);

	return temp;
}

//==============================================================================
// Overloads << for Streams
//==============================================================================
std::ostream& operator<<(std::ostream &strm, const Matrix4f& mat) {
	return strm << mat.m11 << ' ' << mat.m12 << ' ' << mat.m13 << ' ' << mat.m14 << '\n'
				<< mat.m21 << ' ' << mat.m22 << ' ' << mat.m23 << ' ' << mat.m24 << '\n'
				<< mat.m31 << ' ' << mat.m32 << ' ' << mat.m33 << ' ' << mat.m34 << '\n'
				<< mat.m41 << ' ' << mat.m42 << ' ' << mat.m43 << ' ' << mat.m44 << '\n';
}