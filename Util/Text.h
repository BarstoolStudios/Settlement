#ifndef TEXT_H
#define TEXT_H

class Text;

#include <string>
#include "GLMath.h"

class Text {
	static float textureWidth;
	static float textureHeight;
	static float letterWidth;
	static float letterHeight;

	static GLuint VAO;

	static GLuint textureHandle;
	static GLuint shaderProgram;

	static GLuint vboVertexHandle, vboTexCoordHandle;

	static GLint sTransformHandle, sPositionHandle, sTexCoordHandle, sTextureHandle;

	static Vector2i getLetterCoords(int n);

public:
	static void loadResources();
	static void draw(std::string text, Vector2f startPos, float width, Matrix3f transform);
	
};

#endif