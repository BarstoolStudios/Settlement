#include "GL/glew.h"
#include <vector>
#include <iostream>
#include "Terrain/Floor.h"
#include "Util/GLMath.h"
#include "Util/ShaderUtil.h"

std::string Floor::vertexShaderCode =
	"uniform mat4 uMVP;\n"
	"in vec3 iPosition;\n\n"

	"void main() {\n"
	"    gl_Position = uMVP * vec4(iPosition, 1);\n"
	"}\n";

std::string Floor::fragmentShaderCode =
	"uniform vec3 uColor;\n\n"

	"void main() {\n"
	"    gl_FragColor = vec4(uColor, 1);\n"
	"}\n";

GLuint Floor::shaderProgram = -1;

GLuint Floor::vboVertexHandle = -1;

GLuint Floor::VAO = -1;

GLint Floor::sPositionHandle = -1;
GLint Floor::sColorHandle = -1;
GLint Floor::sMVPHandle = -1;

std::vector<GLfloat> Floor::vertices;



Floor::Floor() {
	color = Vector3f(0, 0.35f, 0);
}

void Floor::loadResources() {

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &vboVertexHandle);

	//Vector3f corners[]{Vector3f(-0.5f, 0.5f, 0), Vector3f(-0.5f, -0.5f, 0), Vector3f(0.5f, -0.5f, 0), Vector3f(0.5f, 0.5f, 0)};

	Vector3f corners[]{Vector3f(-32, 0, -32), Vector3f(-32, 0, 32), Vector3f(32, 0, 32), Vector3f(32, 0, -32)};

	corners[0].pushOn(&vertices);
	corners[1].pushOn(&vertices);
	corners[2].pushOn(&vertices);
	corners[0].pushOn(&vertices);
	corners[2].pushOn(&vertices);
	corners[3].pushOn(&vertices);

	int vertexShader = ShaderUtil::loadShader(GL_VERTEX_SHADER, vertexShaderCode);
	ShaderUtil::printShaderStatus("Vertex Shader", vertexShader);

	int fragmentShader = ShaderUtil::loadShader(GL_FRAGMENT_SHADER, fragmentShaderCode);
	ShaderUtil::printShaderStatus("Fragment Shader", fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	ShaderUtil::printProgramStatus(shaderProgram);

	glBindVertexArray(VAO);

	glUseProgram(shaderProgram);

	sPositionHandle = glGetAttribLocation(shaderProgram, "iPosition");
	sColorHandle = glGetUniformLocation(shaderProgram, "uColor");
	sMVPHandle = glGetUniformLocation(shaderProgram, "uMVP");
	
	glBindBuffer(GL_ARRAY_BUFFER, vboVertexHandle);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(sPositionHandle);
	glVertexAttribPointer(sPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Floor::draw(Matrix4f projection, Matrix4f view) {

	Matrix4f VP = projection * view;

	glBindVertexArray(VAO);

	glUseProgram(shaderProgram);

	GLfloat arr[16];
	VP.asArray(arr);
	glUniformMatrix4fv(sMVPHandle, 1, GL_TRUE, arr);

	glUniform3f(sColorHandle, color.x, color.y, color.z);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);

	glBindVertexArray(0);
	glUseProgram(0);
}