/******************************************************************************\
* File: Utility.cpp
*
* Author: Josh Taylor
*
* Header: Utility.h
*
* Description: Provides functions that help but don't really belong anywhere
\******************************************************************************/

#include <GL/glew.h>
#include <vector>
#include <string>
#include <windows.h>
#include "Util/Utility.h"

//==============================================================================
// Returns True When Distance from (x1, y1) to (x2, y2) is < threshold
//==============================================================================
bool Utility::distThreshold(float x1, float y1, float x2, float y2, float threshold) {
	return ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (threshold * threshold);
}

//==============================================================================
// Returns True if str Begins With beg
//==============================================================================
bool Utility::stringStartsWith(std::string& str, std::string beg) {
	if(beg.size() > str.size())
		return false;

	for(int i = 0; i < beg.size(); i++) {
		if(str[i] != beg[i])
			return false;
	}

	return true;
}

//==============================================================================
// Splits str by Delimiter delim and Stores in result
//==============================================================================
void Utility::stringSplit(std::string& str, char delim, std::vector<std::string>& result) {

	int prevLoc = 0;

	for(int i = 0; i < str.size(); i++) {
		if(str[i] == delim) {
			result.push_back(str.substr(prevLoc, i - prevLoc));
			prevLoc = i + 1;
		}
	}

	result.push_back(str.substr(prevLoc));

}

//==============================================================================
// Checks For an openGL Error and Exits if One Occured
//==============================================================================
void Utility::exitOnGLError(std::string errorMessage) {
	GLenum errorValue = glGetError();

	if(errorValue != GL_NO_ERROR) {

		switch(errorValue) {

		case GL_INVALID_ENUM:
			printToOutput(std::string("OpenGL Error: Invalid Enum -- ") + errorMessage + '\n');
			break;

		case GL_INVALID_VALUE:
			printToOutput(std::string("OpenGL Error: Invalid Value -- ") + errorMessage + '\n');
			break;

		case GL_INVALID_OPERATION:
			printToOutput(std::string("OpenGL Error: Invalid Operation -- ") + errorMessage + '\n');
			break;

		case GL_INVALID_FRAMEBUFFER_OPERATION:
			printToOutput(std::string("OpenGL Error: Invalid Framebuffer Operation -- ") + errorMessage + '\n');
			break;

		case GL_OUT_OF_MEMORY:
			printToOutput(std::string("OpenGL Error: Out of Memory -- ") + errorMessage + '\n');
			break;

		case GL_STACK_UNDERFLOW:
			printToOutput(std::string("OpenGL Error: Stack Underflow -- ") + errorMessage + '\n');
			break;

		case GL_STACK_OVERFLOW:
			printToOutput(std::string("OpenGL Error: Stack Overflow -- ") + errorMessage + '\n');
			break;
		}

		exit(EXIT_FAILURE);
	}
}


//==============================================================================
// Prints to Output Window in Visual Studio
//==============================================================================
void Utility::printToOutput(std::string str) {
	OutputDebugString(str.c_str());
}