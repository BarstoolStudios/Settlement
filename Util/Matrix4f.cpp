#include "Util/GLMath.h"

//==============================================================================
// Constructors
//==============================================================================
Matrix4f::Matrix4f() {
	m00 = 1; m10 = 0; m20 = 0; m30 = 0;
	m01 = 0; m11 = 1; m21 = 0; m31 = 0;
	m02 = 0; m12 = 0; m22 = 1; m32 = 0;
	m03 = 0; m13 = 0; m23 = 0; m33 = 1;
}

Matrix4f::Matrix4f(Matrix4f& mat) {
	m00 = mat.m00; m10 = mat.m10; m20 = mat.m20; m30 = mat.m30;
	m01 = mat.m01; m11 = mat.m11; m21 = mat.m21; m31 = mat.m31;
	m02 = mat.m02; m12 = mat.m12; m22 = mat.m22; m32 = mat.m32;
	m03 = mat.m03; m13 = mat.m13; m23 = mat.m23; m33 = mat.m33;
}

Matrix4f::Matrix4f(
	GLfloat m00, GLfloat m10, GLfloat m20, GLfloat m30,
	GLfloat m01, GLfloat m11, GLfloat m21, GLfloat m31,
	GLfloat m02, GLfloat m12, GLfloat m22, GLfloat m32,
	GLfloat m03, GLfloat m13, GLfloat m23, GLfloat m33)
	:
	m00(m00), m10(m10), m20(m20), m30(m30),
	m01(m01), m11(m11), m21(m21), m31(m31),
	m02(m02), m12(m12), m22(m22), m32(m32),
	m03(m03), m13(m13), m23(m23), m33(m33)
	{}

//==============================================================================
// Returns Matrix as Array (Row-Major)
//==============================================================================
void Matrix4f::asArray(GLfloat* arr) {
	arr[0] = m00; arr[1] = m10; arr[2] = m20; arr[3] = m30;
	arr[4] = m01; arr[5] = m11; arr[6] = m21; arr[7] = m31;
	arr[8] = m02; arr[9] = m12; arr[10] = m22; arr[11] = m32;
	arr[12] = m03; arr[13] = m13; arr[14] = m23; arr[15] = m33;
}

//==============================================================================
// Takes Transpose of Current Matrix (In Place)
//==============================================================================
void Matrix4f::transpose() {
	Matrix4f temp(*this);

	m01 = temp.m10;
	m02 = temp.m20;
	m03 = temp.m30;

	m10 = temp.m01;
	m12 = temp.m21;
	m13 = temp.m31;

	m20 = temp.m02;
	m21 = temp.m12;
	m23 = temp.m32;

	m30 = temp.m03;
	m31 = temp.m13;
	m32 = temp.m23;
}

//==============================================================================
// Takes Inverse of Current Matrix (In Place)
//==============================================================================
void Matrix4f::inverse() {
	// Find Inverse Determinant
	GLfloat invDet = 1.0f / determinant();

	// Find Cofactors
	GLfloat c00 = Matrix3f(m11, m21, m31, m12, m22, m32, m13, m23, m33).determinant();
	GLfloat c01 = Matrix3f(m10, m20, m30, m12, m22, m32, m13, m23, m33).determinant();
	GLfloat c02 = Matrix3f(m10, m20, m30, m11, m21, m31, m13, m23, m33).determinant();
	GLfloat c03 = Matrix3f(m10, m20, m30, m11, m21, m31, m12, m22, m32).determinant();

	GLfloat c10 = Matrix3f(m01, m21, m31, m02, m22, m32, m03, m23, m33).determinant();
	GLfloat c11 = Matrix3f(m00, m20, m30, m02, m22, m32, m03, m23, m33).determinant();
	GLfloat c12 = Matrix3f(m00, m20, m30, m01, m21, m31, m03, m23, m33).determinant();
	GLfloat c13 = Matrix3f(m00, m20, m30, m01, m21, m31, m02, m22, m32).determinant();

	GLfloat c20 = Matrix3f(m01, m11, m31, m02, m12, m32, m03, m13, m33).determinant();
	GLfloat c21 = Matrix3f(m00, m10, m30, m02, m12, m32, m03, m13, m33).determinant();
	GLfloat c22 = Matrix3f(m00, m10, m30, m01, m11, m31, m03, m13, m33).determinant();
	GLfloat c23 = Matrix3f(m00, m10, m30, m01, m11, m31, m02, m12, m32).determinant();

	GLfloat c30 = Matrix3f(m01, m11, m21, m02, m12, m22, m03, m13, m23).determinant();
	GLfloat c31 = Matrix3f(m00, m10, m20, m02, m12, m22, m03, m13, m23).determinant();
	GLfloat c32 = Matrix3f(m00, m10, m20, m01, m11, m21, m03, m13, m23).determinant();
	GLfloat c33 = Matrix3f(m00, m10, m20, m01, m11, m21, m02, m12, m22).determinant();

	// Multiply by Inverse Determinant
	m00 = c00 * invDet;
	m01 = c01 * invDet;
	m02 = c02 * invDet;
	m03 = c03 * invDet;

	m10 = c10 * invDet;
	m11 = c11 * invDet;
	m12 = c12 * invDet;
	m13 = c13 * invDet;

	m20 = c20 * invDet;
	m21 = c21 * invDet;
	m22 = c22 * invDet;
	m23 = c23 * invDet;

	m30 = c30 * invDet;
	m31 = c31 * invDet;
	m32 = c32 * invDet;
	m33 = c33 * invDet;
}

//==============================================================================
// Returns Determinate of Current Matrix
//==============================================================================
GLfloat Matrix4f::determinant() {
	return	 m00 * Matrix3f(m11, m21, m31, m12, m22, m32, m13, m23, m33).determinant()
			-m01 * Matrix3f(m10, m20, m30, m12, m22, m32, m13, m23, m33).determinant()
			+m02 * Matrix3f(m10, m20, m30, m11, m21, m31, m13, m23, m33).determinant()
			-m03 * Matrix3f(m10, m20, m30, m12, m22, m32, m13, m23, m33).determinant();
}

//==============================================================================
// Matrix Matrix Multiplication
//==============================================================================
Matrix4f Matrix4f::operator * (const Matrix4f& m) {
	Matrix4f temp;

	Vector4f c0(m.m00, m.m01, m.m02, m.m03);
	Vector4f c1(m.m10, m.m11, m.m12, m.m13);
	Vector4f c2(m.m20, m.m21, m.m22, m.m23);
	Vector4f c3(m.m30, m.m31, m.m32, m.m33);

	Vector4f r0(m00, m10, m20, m30);
	Vector4f r1(m01, m11, m21, m31);
	Vector4f r2(m02, m12, m22, m32);
	Vector4f r3(m03, m13, m23, m33);

	temp.m00 = Vector4f::dot(c0, r0);
	temp.m01 = Vector4f::dot(c0, r1);
	temp.m02 = Vector4f::dot(c0, r2);
	temp.m03 = Vector4f::dot(c0, r3);

	temp.m10 = Vector4f::dot(c1, r0);
	temp.m11 = Vector4f::dot(c1, r1);
	temp.m12 = Vector4f::dot(c1, r2);
	temp.m13 = Vector4f::dot(c1, r3);

	temp.m20 = Vector4f::dot(c2, r0);
	temp.m21 = Vector4f::dot(c2, r1);
	temp.m22 = Vector4f::dot(c2, r2);
	temp.m23 = Vector4f::dot(c2, r3);

	temp.m30 = Vector4f::dot(c3, r0);
	temp.m31 = Vector4f::dot(c3, r1);
	temp.m32 = Vector4f::dot(c3, r2);
	temp.m33 = Vector4f::dot(c3, r3);

	return temp;
}

//==============================================================================
// Matrix Vector Multiplication
//==============================================================================
Vector4f Matrix4f::operator * (const Vector4f& v) {
	Vector4f temp;

	Vector4f r0(m00, m10, m20, m30);
	Vector4f r1(m01, m11, m21, m31);
	Vector4f r2(m02, m12, m22, m32);
	Vector4f r3(m03, m13, m23, m33);

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
	return strm << mat.m00 << ' ' << mat.m10 << ' ' << mat.m20 << ' ' << mat.m30 << '\n'
				<< mat.m01 << ' ' << mat.m11 << ' ' << mat.m21 << ' ' << mat.m31 << '\n'
				<< mat.m02 << ' ' << mat.m12 << ' ' << mat.m22 << ' ' << mat.m32 << '\n'
				<< mat.m03 << ' ' << mat.m13 << ' ' << mat.m23 << ' ' << mat.m33 << '\n';
}