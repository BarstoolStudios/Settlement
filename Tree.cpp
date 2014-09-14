#include "Tree.h"
#include "GLMath.h"
#include "ShaderUtil.h"

GLuint Tree::VAO = 0;
GLuint Tree::shaderProgram = 0;
GLuint Tree::verticesVBO = 0;
GLuint Tree::normalsVBO = 0;

GLint Tree::sPositionHandle = 0;
GLint Tree::sNormalHandle = 0;
GLint Tree::sSunHandle = 0;
GLint Tree::sMVPHandle = 0;
GLint Tree::sNormalMatrixHandle = 0;

int Tree::vertCount = 0;

Tree::Tree(Vector3f position) 
	:
	position(position)
	{}

void Tree::loadResources() {

	shaderProgram = ShaderUtil::createProgram("Tree", std::vector < GLenum > {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER}, true);

	sPositionHandle = glGetAttribLocation(shaderProgram, "iPosition");
	sNormalHandle = glGetAttribLocation(shaderProgram, "iNormal");
	sSunHandle = glGetUniformLocation(shaderProgram, "uSunDirection");
	sMVPHandle = glGetUniformLocation(shaderProgram, "uMVP");
	sNormalMatrixHandle = glGetUniformLocation(shaderProgram, "uNormalMatrix");

	ModelData data = ShaderUtil::loadModel("Tree");

	verticesVBO = data.getVerticesVBO();
	normalsVBO = data.getNormalsVBO();
	vertCount = data.getVertCount();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glUseProgram(shaderProgram);

	//------------------------------------------------------------------------------
	// Load Vertex Data
	//------------------------------------------------------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glEnableVertexAttribArray(sPositionHandle);
	glVertexAttribPointer(sPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//------------------------------------------------------------------------------
	// Load Normal Data
	//------------------------------------------------------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
	glEnableVertexAttribArray(sNormalHandle);
	glVertexAttribPointer(sNormalHandle, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Tree::draw(Matrix4f projection, Matrix4f view, Vector3f sunDirection) {
	//------------------------------------------------------------------------------
	// Create Model Matrix
	//------------------------------------------------------------------------------
	Matrix4f model = GLMath::getTranslation(position.x, position.y, position.z);

	//------------------------------------------------------------------------------
	// Create ModelView Matrix
	//------------------------------------------------------------------------------
	Matrix4f modelView = view * model;

	//------------------------------------------------------------------------------
	// Create MVP Matrix
	//------------------------------------------------------------------------------
	Matrix4f MVP = projection * view;

	//------------------------------------------------------------------------------
	// Create Normal Matrix
	//------------------------------------------------------------------------------
	Matrix4f temp(model);
	temp.inverse();
	temp.transpose();
	Matrix3f nMatrix(temp);

	//------------------------------------------------------------------------------
	// Bind Vertex Array Object
	//------------------------------------------------------------------------------
	glBindVertexArray(VAO);

	//------------------------------------------------------------------------------
	// Use Shader Program
	//------------------------------------------------------------------------------
	glUseProgram(shaderProgram);

	//------------------------------------------------------------------------------
	// Associate Sun Direction
	//------------------------------------------------------------------------------
	glUniform3f(sSunHandle, sunDirection.x, sunDirection.y, sunDirection.z);

	//------------------------------------------------------------------------------
	// Load MVP Matrix 
	//------------------------------------------------------------------------------
	GLfloat arrMVP[16];
	MVP.asArray(arrMVP);
	glUniformMatrix4fv(sMVPHandle, 1, GL_TRUE, arrMVP);

	//------------------------------------------------------------------------------
	// Load Normal Matrix 
	//------------------------------------------------------------------------------
	GLfloat arrNorm[9];
	nMatrix.asArray(arrNorm);
	glUniformMatrix3fv(sNormalMatrixHandle, 1, GL_TRUE, arrNorm);

	//------------------------------------------------------------------------------
	// Unbind / Disable Code
	//------------------------------------------------------------------------------
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}