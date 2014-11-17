#ifndef SHADERUTIL_H
#define SHADERUTIL_H

#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "Util/GLMath.h"
#include "Models/ModelData.h"

namespace ShaderUtil {

	GLint loadShader(GLenum type, std::string shaderCode);

	std::string readShaderFromFile(std::string shaderName);

	GLint createProgram(std::string modelName, std::vector<GLenum> shaders, bool printStatus);

	GLuint loadPNG(std::string pngName);

	ModelData loadModel(std::string modelName);

	void printShaderStatus(std::string message, GLint handle);

	void printProgramStatus(GLint handle);

}

#endif // SHADERUTIL_H