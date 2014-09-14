#include <GL\glew.h>
#include "math.h"
#include <iostream>
#include <vector>
#include "ModelData.h"

namespace ShaderUtil {
	GLint loadShader(GLenum type, std::string shaderCode);

	std::string readShaderFromFile(std::string shaderName);

	GLint createProgram(std::string modelName, std::vector<GLenum> shaders, bool printStatus);

	GLint loadPNG(std::string pngName);

	ModelData loadModel(std::string modelName);

	void exitOnGLError(std::string errorMessage);

	void printShaderStatus(std::string message, GLint handle);

	void printProgramStatus(GLint handle);

	void printToOutput(std::string str);
}