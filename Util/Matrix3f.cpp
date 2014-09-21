#include "Util/GLMath.h"

//==============================================================================
// Constructors
//==============================================================================
Matrix3f::Matrix3f() {
	m00 = 1; m10 = 0; m20 = 0;
	m01 = 0; m11 = 1; m21 = 0;
	m02 = 0; m12 = 0; m22 = 1;
}

Matrix3f::Matrix3f(Matrix3f& mat) {
	m00 = mat.m00; m10 = mat.m10; m20 = mat.m20;
	m01 = mat.m01; m11 = mat.m11; m21 = mat.m21;
	m02 = mat.m02; m12 = mat.m12; m22 = mat.m22;
}

Matrix3f::Matrix3f(Matrix4f& mat) {
	m00 = mat.m00; m10 = mat.m10; m20 = mat.m20;
	m01 = mat.m01; m11 = mat.m11; m21 = mat.m21;
	m02 = mat.m02; m12 = mat.m12; m22 = mat.m22;
}

Matrix3f::Matrix3f(
	GLfloat m00, GLfloat m10, GLfloat m20,
	GLfloat m01, GLfloat m11, GLfloat m21,
	GLfloat m02, GLfloat m12, GLfloat m22)
	:
	m00(m00), m10(m10), m20(m20),
	m01(m01), m11(m11), m21(m21),
	m02(m02), m12(m12), m22(m22)
	{}

//==============================================================================
// Returns Matrix as Array (Row-Major)
//==============================================================================
void Matrix3f::asArray(GLfloat* arr) {
	arr[0] = m00; arr[1] = m10; arr[2] = m20;
	arr[3] = m01; arr[4] = m11; arr[5] = m21;
	arr[6] = m02; arr[7] = m12; arr[8] = m22;
}

//==============================================================================
// Takes Transpose of Current Matrix (In Place)
//==============================================================================
void Matrix3f::transpose() {
	Matrix3f temp(*this);

	m01 = temp.m10;
	m02 = temp.m20;
	
	m10 = temp.m01;
	m12 = temp.m21;

	m20 = temp.m02;
	m21 = temp.m12;
}

//==============================================================================
// Takes Inverse of Current Matrix (In Place)
//==============================================================================
void Matrix3f::inverse() {
	// Find Inverse Determinant
	GLfloat invDet = 1.0f / determinant();

	// Find Cofactors
	GLfloat c00 = Matrix2f(m11, m21, m12, m22).determinant();
	GLfloat c01 = -Matrix2f(m10, m20, m12, m22).determinant();
	GLfloat c02 = Matrix2f(m10, m20, m11, m21).determinant();

	GLfloat c10 = -Matrix2f(m01, m21, m02, m22).determinant();
	GLfloat c11 = Matrix2f(m00, m20, m02, m22).determinant();
	GLfloat c12 = -Matrix2f(m00, m20, m01, m21).determinant();

	GLfloat c20 = Matrix2f(m01, m11, m02, m12).determinant();
	GLfloat c21 = -Matrix2f(m00, m10, m02, m12).determinant();
	GLfloat c22 = Matrix2f(m00, m10, m01, m11).determinant();

	// Multiply by Inverse Determinant
	m00 = c00 * invDet;
	m01 = c01 * invDet;
	m02 = c02 * invDet;

	m10 = c10 * invDet;
	m11 = c11 * invDet;
	m12 = c12 * invDet;

	m20 = c20 * invDet;
	m21 = c21 * invDet;
	m22 = c22 * invDet;
}

//==============================================================================
// Returns Determinate of Current Matrix
//==============================================================================
GLfloat Matrix3f::determinant() {
	
	return	 m00 * Matrix2f(m11, m21, m12, m22).determinant()
			-m01 * Matrix2f(m10, m20, m12, m22).determinant()
			+m02 * Matrix2f(m10, m20, m11, m21).determinant();

}

//==============================================================================
// Matrix Matrix Multiplication
//==============================================================================
Matrix3f Matrix3f::operator * (const Matrix3f& m) {
	Matrix3f temp;

	Vector3f c0(m.m00, m.m01, m.m02);
	Vector3f c1(m.m10, m.m11, m.m12);
	Vector3f c2(m.m20, m.m21, m.m22);

	Vector3f r0(m00, m10, m20);
	Vector3f r1(m01, m11, m21);
	Vector3f r2(m02, m12, m22);

	temp.m00 = Vector3f::dot(c0, r0);
	temp.m01 = Vector3f::dot(c0, r1);
	temp.m02 = Vector3f::dot(c0, r2);

	temp.m10 = Vector3f::dot(c1, r0);
	temp.m11 = Vector3f::dot(c1, r1);
	temp.m12 = Vector3f::dot(c1, r2);

	temp.m20 = Vector3f::dot(c2, r0);
	temp.m21 = Vector3f::dot(c2, r1);
	temp.m22 = Vector3f::dot(c2, r2);

	return temp;
}

//==============================================================================
// Matrix Vector Multiplication
//==============================================================================
Vector3f Matrix3f::operator * (const Vector3f& v) {
	Vector3f temp;

	Vector3f r0(m00, m10, m20);
	Vector3f r1(m01, m11, m21);
	Vector3f r2(m02, m12, m22);

	temp.x = Vector3f::dot(v, r0);
	temp.y = Vector3f::dot(v, r1);
	temp.z = Vector3f::dot(v, r2);

	return temp;
}

//==============================================================================
// Overloads << for Streams
//==============================================================================
std::ostream& operator<<(std::ostream &strm, const Matrix3f& mat) {
	return strm << mat.m00 << ' ' << mat.m10 << ' ' << mat.m20 << '\n'
				<< mat.m01 << ' ' << mat.m11 << ' ' << mat.m21 << '\n'
				<< mat.m02 << ' ' << mat.m12 << ' ' << mat.m22 << '\n';
}