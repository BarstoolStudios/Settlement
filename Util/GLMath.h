#ifndef GLMATH_H
#define GLMATH_H

class Vector4f;
class Vector4i;
class Vector3f;
class Vector3i;
class Vector2f;
class Vector2i;
class Matrix4f;
class Matrix3f;
class Matrix2f;

#include <GL/glew.h>
#include <ostream>
#include <vector>

#define PI_F 3.141592f
#define PI_D 3.14159265358979323846

class Vector4f {
public:
	GLfloat x, y, z, w;

	Vector4f();
	Vector4f(const Vector4f& vec);
	Vector4f(GLfloat, GLfloat, GLfloat, GLfloat);

	void pushOn(std::vector<GLfloat>* floats);

	Vector4f operator + (const Vector4f&);
	Vector4f operator - (const Vector4f&);
	Vector4f operator * (const Vector4f&);
	Vector4f operator / (const Vector4f&);

	Vector4f operator += (const Vector4f&);
	Vector4f operator -= (const Vector4f&);
	Vector4f operator *= (const Vector4f&);
	Vector4f operator /= (const Vector4f&);

	Vector4f operator + (float);
	Vector4f operator - (float);
	Vector4f operator * (float);
	Vector4f operator / (float);

	Vector4f operator += (float);
	Vector4f operator -= (float);
	Vector4f operator *= (float);
	Vector4f operator /= (float);

	std::string toString();

	static GLfloat dot(const Vector4f&, const Vector4f&);
};

std::ostream& operator<<(std::ostream &strm, const Vector4f& vec);

class Vector4i {
public:
	GLint x, y, z, w;

	Vector4i();
	Vector4i(const Vector4i& vec);
	Vector4i(GLint, GLint, GLint, GLint);

	void pushOn(std::vector<GLint>* floats);

	Vector4i operator + (const Vector4i&);
	Vector4i operator - (const Vector4i&);
	Vector4i operator * (const Vector4i&);
	Vector4i operator / (const Vector4i&);

	Vector4i operator += (const Vector4i&);
	Vector4i operator -= (const Vector4i&);
	Vector4i operator *= (const Vector4i&);
	Vector4i operator /= (const Vector4i&);

	Vector4i operator + (int);
	Vector4i operator - (int);
	Vector4i operator * (int);
	Vector4i operator / (int);

	Vector4i operator += (int);
	Vector4i operator -= (int);
	Vector4i operator *= (int);
	Vector4i operator /= (int);

	bool operator == (const Vector4i&);
	bool operator != (const Vector4i&);

	std::string toString();

	static GLint dot(const Vector4i&, const Vector4i&);
};

std::ostream& operator<<(std::ostream &strm, const Vector4i& vec);



class Vector3f {
	public:
		GLfloat x, y, z;

		Vector3f();
		Vector3f(const Vector3f& vec);
		Vector3f(GLfloat, GLfloat, GLfloat);

		void pushOn(std::vector<GLfloat>* floats);

		Vector3f operator + (const Vector3f&);
		Vector3f operator - (const Vector3f&);
		Vector3f operator * (const Vector3f&);
		Vector3f operator / (const Vector3f&);

		Vector3f operator += (const Vector3f&);
		Vector3f operator -= (const Vector3f&);
		Vector3f operator *= (const Vector3f&);
		Vector3f operator /= (const Vector3f&);

		Vector3f operator + (float);
		Vector3f operator - (float);
		Vector3f operator * (float);
		Vector3f operator / (float);

		Vector3f operator += (float);
		Vector3f operator -= (float);
		Vector3f operator *= (float);
		Vector3f operator /= (float);

		std::string toString();

		static GLfloat dot(const Vector3f&, const Vector3f&);
		static Vector3f cross(const Vector3f&, const Vector3f&);
		static Vector3f norm(const Vector3f&);

};

std::ostream& operator<<(std::ostream &strm, const Vector3f& vec);

class Vector3i {
public:
	GLint x, y, z;

	Vector3i();
	Vector3i(const Vector3i& vec);
	Vector3i(GLint, GLint, GLint);

	void pushOn(std::vector<GLint>* floats);

	Vector3i operator + (const Vector3i&);
	Vector3i operator - (const Vector3i&);
	Vector3i operator * (const Vector3i&);
	Vector3i operator / (const Vector3i&);

	Vector3i operator += (const Vector3i&);
	Vector3i operator -= (const Vector3i&);
	Vector3i operator *= (const Vector3i&);
	Vector3i operator /= (const Vector3i&);

	Vector3i operator + (int);
	Vector3i operator - (int);
	Vector3i operator * (int);
	Vector3i operator / (int);

	Vector3i operator += (int);
	Vector3i operator -= (int);
	Vector3i operator *= (int);
	Vector3i operator /= (int);

	bool operator == (const Vector3i&);
	bool operator != (const Vector3i&);

	std::string toString();

	static GLint dot(const Vector3i&, const Vector3i&);
	static Vector3i cross(const Vector3i&, const Vector3i&);
};

std::ostream& operator<<(std::ostream &strm, const Vector3i& vec);



class Vector2f {
	public:
		GLfloat x, y;

		Vector2f();
		Vector2f(const Vector2f& vec);
		Vector2f(GLfloat, GLfloat);

		void pushOn(std::vector<GLfloat>* floats);

		Vector2f operator + (const Vector2f&);
		Vector2f operator - (const Vector2f&);
		Vector2f operator * (const Vector2f&);
		Vector2f operator / (const Vector2f&);

		Vector2f operator += (const Vector2f&);
		Vector2f operator -= (const Vector2f&);
		Vector2f operator *= (const Vector2f&);
		Vector2f operator /= (const Vector2f&);

		Vector2f operator + (float);
		Vector2f operator - (float);
		Vector2f operator * (float);
		Vector2f operator / (float);

		Vector2f operator += (float);
		Vector2f operator -= (float);
		Vector2f operator *= (float);
		Vector2f operator /= (float);

		std::string toString();

		static GLfloat dot(const Vector2f&, const Vector2f&);
};

std::ostream& operator<<(std::ostream &strm, const Vector2f& vec);

class Vector2i {
public:
	GLint x, y;

	Vector2i();
	Vector2i(const Vector2i& vec);
	Vector2i(GLint, GLint);

	void pushOn(std::vector<GLint>* floats);

	Vector2i operator + (const Vector2i&);
	Vector2i operator - (const Vector2i&);
	Vector2i operator * (const Vector2i&);
	Vector2i operator / (const Vector2i&);

	Vector2i operator += (const Vector2i&);
	Vector2i operator -= (const Vector2i&);
	Vector2i operator *= (const Vector2i&);
	Vector2i operator /= (const Vector2i&);

	Vector2i operator + (int);
	Vector2i operator - (int);
	Vector2i operator * (int);
	Vector2i operator / (int);

	Vector2i operator += (int);
	Vector2i operator -= (int);
	Vector2i operator *= (int);
	Vector2i operator /= (int);

	bool operator == (const Vector2i&);
	bool operator != (const Vector2i&);

	std::string toString();

	static GLint dot(const Vector2i&, const Vector2i&);
};

std::ostream& operator<<(std::ostream &strm, const Vector2i& vec);



class Matrix4f {
	public:
		GLfloat	m11, m12, m13, m14,
				m21, m22, m23, m24,
				m31, m32, m33, m34,
				m41, m42, m43, m44;
		
		Matrix4f();
		Matrix4f(Matrix4f& mat);
		Matrix4f(
					GLfloat, GLfloat, GLfloat, GLfloat,
					GLfloat, GLfloat, GLfloat, GLfloat,
					GLfloat, GLfloat, GLfloat, GLfloat,
					GLfloat, GLfloat, GLfloat, GLfloat
				);

		void pushOn(std::vector<GLfloat>* floats);

		void asArray(GLfloat* arr);

		void transpose();
		void inverse();
		GLfloat determinant();

		Matrix4f operator * (const Matrix4f&);
		Vector4f operator * (const Vector4f&);
};

std::ostream& operator<<(std::ostream &strm, const Matrix4f& mat);

class Matrix3f {
	public:
		GLfloat	m11, m12, m13,
				m21, m22, m23,
				m31, m32, m33;

		Matrix3f();
		Matrix3f(Matrix3f& mat);
		Matrix3f(Matrix4f& mat);
		Matrix3f(
					GLfloat, GLfloat, GLfloat,
					GLfloat, GLfloat, GLfloat,
					GLfloat, GLfloat, GLfloat
				);


		void asArray(GLfloat* arr);

		void transpose();
		void inverse();
		GLfloat determinant();

		Matrix3f operator * (const Matrix3f&);
		Vector3f operator * (const Vector3f&);
};

std::ostream& operator<<(std::ostream &strm, const Matrix3f& vec);

class Matrix2f {
public:
	GLfloat	m11, m12,
			m21, m22;

	Matrix2f();
	Matrix2f(Matrix2f& mat);

	Matrix2f(	
				GLfloat, GLfloat,
				GLfloat, GLfloat
			);

	void asArray(GLfloat* arr);

	void transpose();
	void inverse();
	GLfloat determinant();

	Matrix2f operator * (const Matrix2f&);
	Vector2f operator * (const Vector2f&);
};

std::ostream& operator<<(std::ostream &strm, const Matrix2f& vec);

namespace GLMath {
	Matrix4f getPerspective(float fov, float height, float width, float zNear, float zFar);

	Matrix4f getOrthographic(float height, float width, float zNear, float zFar, float scalingFactor);

	Matrix3f getTransform2D(float height, float width);

	Matrix4f getTranslation(float x, float y, float z);

	Matrix4f getTranslation(Vector3f vec);

	Matrix4f getScale(float x, float y, float z);

	Matrix4f getScale(Vector3f vec);

	Matrix4f getRotation(float x, float y, float z);

	Matrix4f getRotation(Vector3f vec);

	Matrix3f fourToThree(const Matrix4f& m4);
}
#endif