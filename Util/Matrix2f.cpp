#include "Util/GLMath.h"

//==============================================================================
// Constructors
//==============================================================================
Matrix2f::Matrix2f() {
	m00 = 0; m10 = 0;
	m01 = 0; m11 = 0;
}

Matrix2f::Matrix2f(
	GLfloat m00, GLfloat m10,
	GLfloat m01, GLfloat m11)
	:
	m00(m00), m10(m10),
	m01(m01), m11(m11)
	{}

Matrix2f::Matrix2f(Matrix2f& mat) {
	m00 = mat.m00; m10 = mat.m10;
	m01 = mat.m01; m11 = mat.m11;
}

//==============================================================================
// Returns Matrix as Array (Row-Major)
//==============================================================================
void Matrix2f::asArray(GLfloat* arr) {
	arr[0] = m00; arr[1] = m10;
	arr[2] = m01; arr[3] = m11;
}

//==============================================================================
// Takes Transpose of Current Matrix (In Place)
//==============================================================================
void Matrix2f::transpose() {
	Matrix2f temp(*this);

	m01 = temp.m10;
	m10 = temp.m01;
}

//==============================================================================
// Takes Inverse of Current Matrix (In Place)
//==============================================================================
void Matrix2f::inverse() {

	GLfloat a = m00;
	GLfloat d = m11;

	GLfloat invDet = 1.0f / determinant();

	m00 = d * invDet;
	m11 = a * invDet;

	m10 *= -invDet;
	m01 *= -invDet;
}

//==============================================================================
// Returns Determinate of Current Matrix
//==============================================================================
GLfloat Matrix2f::determinant() {
	return (m00 * m11) - (m10 * m01);
}

//==============================================================================
// Matrix Matrix Multiplication
//==============================================================================
Matrix2f Matrix2f::operator * (const Matrix2f& m) {
	Matrix2f temp;

	Vector2f c0(m.m00, m.m01);
	Vector2f c1(m.m10, m.m11);

	Vector2f r0(m00, m10);
	Vector2f r1(m01, m11);

	temp.m00 = Vector2f::dot(c0, r0);
	temp.m01 = Vector2f::dot(c0, r1);

	temp.m10 = Vector2f::dot(c1, r0);
	temp.m11 = Vector2f::dot(c1, r1);

	return temp;
}

//==============================================================================
// Matrix Vector Multiplication
//==============================================================================
Vector2f Matrix2f::operator * (const Vector2f& v) {
	Vector2f temp;

	Vector2f r0(m00, m10);
	Vector2f r1(m01, m11);

	temp.x = Vector2f::dot(v, r0);
	temp.y = Vector2f::dot(v, r1);

	return temp;
}

//==============================================================================
// Overloads << for Streams
//==============================================================================
std::ostream& operator<<(std::ostream &strm, const Matrix2f& mat) {
	return strm << mat.m00 << ' ' << mat.m10 << '\n'
				<< mat.m01 << ' ' << mat.m11 << '\n';
}