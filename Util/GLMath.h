#ifndef GLMATH_H
#define GLMATH_H

#include <GL/glew.h>
#include <ostream>
#include <vector>



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

	std::string toString();

	static GLfloat dot(const Vector4f&, const Vector4f&);
};

std::ostream& operator<<(std::ostream &strm, const Vector4f& vec);

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

		std::string toString();

		static GLfloat dot(const Vector3f&, const Vector3f&);
		static Vector3f cross(const Vector3f&, const Vector3f&);
		static Vector3f norm(const Vector3f&);

};

std::ostream& operator<<(std::ostream &strm, const Vector3f& vec);

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

		std::string toString();

		static GLfloat dot(const Vector2f&, const Vector2f&);
};

std::ostream& operator<<(std::ostream &strm, const Vector2f& vec);

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