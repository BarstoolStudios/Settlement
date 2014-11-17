/******************************************************************************\
* File: Text.cpp
*
* Author: Josh Taylor
*
* Header: Text.h
*
* Description: Class that draws text to the screen
\******************************************************************************/

#include "Util/Text.h"
#include <GL/glew.h>
#include <vector>
#include "Util/ShaderUtil.h"
#include "Util/Utility.h"

//==============================================================================
// Initialize Static Variables
//==============================================================================
float Text::textureWidth = 256;
float Text::textureHeight = 512;

float Text::letterWidth = 24;
float Text::letterHeight = 36;

GLuint Text::VAO = 0;

GLuint Text::textureHandle = 0;
GLuint Text::shaderProgram = 0;

GLuint Text::vboVertexHandle = 0;
GLuint Text::vboTexCoordHandle = 0;

GLint Text::sTransformHandle = -1;
GLint Text::sPositionHandle = -1;
GLint Text::sTexCoordHandle = -1;
GLint Text::sTextureHandle = -1;

//==============================================================================
// Loads Static Resources
//==============================================================================
void Text::loadResources() {
	textureHandle = ShaderUtil::loadPNG("alphabet_48.png");

	shaderProgram = ShaderUtil::createProgram("Text", std::vector < GLenum > {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER}, true);
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint buffs[2];
	glGenBuffers(2, buffs);
	vboVertexHandle = buffs[0];
	vboTexCoordHandle = buffs[1];

	sTransformHandle = glGetUniformLocation(shaderProgram, "uTransform");
	sPositionHandle = glGetAttribLocation(shaderProgram, "iPosition");
	sTexCoordHandle = glGetAttribLocation(shaderProgram, "iTexCoord");
	sTextureHandle = glGetUniformLocation(shaderProgram, "uTexture");

}

//==============================================================================
// Draws Text On Screen Where startPos is Top-Left Corner of First Letter
//==============================================================================
void Text::draw(std::string text, Vector2f startPos, float width, Matrix3f transform) {
	if(text.size() == 0)
		return;
	
	float height = width * 1.5f;

	Vector2f curr(startPos);

	Vector2f v1, v2, v3, v4;
	Vector2f t1, t2, t3, t4;

	std::vector<GLfloat> positions;
	std::vector<GLfloat> texCoords;

	for(int i = 0; i < text.size(); i++) {
		int iChar = (int) text[i];

		if(iChar > 32 && iChar < 127) {
			Vector2i letterCoord = getLetterCoords(iChar);

			v1 = Vector2f(curr.x, curr.y);
			t1 = Vector2f(letterCoord.x * letterWidth / textureWidth, letterCoord.y * letterHeight / textureHeight);

			v2 = Vector2f(curr.x, curr.y + height);
			t2 = Vector2f(letterCoord.x * letterWidth / textureWidth, (letterCoord.y + 1) * letterHeight / textureHeight);

			v3 = Vector2f(curr.x + width, curr.y + height);
			t3 = Vector2f((letterCoord.x + 1) * letterWidth / textureWidth, (letterCoord.y + 1) * letterHeight / textureHeight);

			v4 = Vector2f(curr.x + width, curr.y);
			t4 = Vector2f((letterCoord.x + 1) * letterWidth / textureWidth, letterCoord.y * letterHeight / textureHeight);
			
			v1.pushOn(&positions);
			t1.pushOn(&texCoords);

			v2.pushOn(&positions);
			t2.pushOn(&texCoords);

			v3.pushOn(&positions);
			t3.pushOn(&texCoords);

			v1.pushOn(&positions);
			t1.pushOn(&texCoords);

			v3.pushOn(&positions);
			t3.pushOn(&texCoords);

			v4.pushOn(&positions);
			t4.pushOn(&texCoords);

			curr.x += width;
		
		} else if(iChar == 32) {
			// SPACE
			curr.x += width;

		} else if(iChar == 9) {
			// TAB
			curr.x += (width * 4);

		} else if(iChar == 10) {
			// NEW LINE
			curr.x = startPos.x;
			curr.y += height;

		} else {
			Utility::printToOutput("Error -- Unsupported Character.");
			exit(-1);
		}
	}

	GLfloat arrTransform[9];
	transform.asArray(arrTransform);

	glBindVertexArray(VAO);

	glUseProgram(shaderProgram);

	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glUniform1i(sTextureHandle, 0);

	glUniformMatrix3fv(sTransformHandle, 1, GL_TRUE, arrTransform);

	glBindBuffer(GL_ARRAY_BUFFER, vboVertexHandle);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(GLfloat), &(positions[0]), GL_STATIC_DRAW);
	glEnableVertexAttribArray(sPositionHandle);
	glVertexAttribPointer(sPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, vboTexCoordHandle);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(GLfloat), &(texCoords[0]), GL_STATIC_DRAW);
	glEnableVertexAttribArray(sTexCoordHandle);
	glVertexAttribPointer(sTexCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, (int)positions.size() / 2);

	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//==============================================================================
// Gets the Grid Coordinate of Letter
//==============================================================================
Vector2i Text::getLetterCoords(int n) {
	return Vector2i((n - 33) % 10, (n - 33) / 10);
}