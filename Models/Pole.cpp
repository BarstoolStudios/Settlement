#include "Models/Pole.h"
#include "Util/ShaderUtil.h"

//==============================================================================
// Initialize Static Variables
//==============================================================================
GLuint Pole::VAO = 0;
GLuint Pole::shaderProgram = 0;
GLuint Pole::verticesVBO = 0;
GLuint Pole::normalsVBO = 0;

GLint Pole::sPositionHandle = 0;
GLint Pole::sNormalHandle = 0;
GLint Pole::sSunHandle = 0;
GLint Pole::sMVPHandle = 0;
GLint Pole::sNormalMatrixHandle = 0;

int Pole::vertCount = 0;

Pole::Pole(Vector3f position, Vector3f color)
:
	position(position),
	color(color)
{}

//==============================================================================
// Loads Model Data into OpenGL and Stores Handles in Static Variables
//==============================================================================
void Pole::loadResources() {
	shaderProgram = ShaderUtil::createProgram("Pole", std::vector < GLenum > {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER}, true);

	sPositionHandle = glGetAttribLocation(shaderProgram, "iPosition");
	sNormalHandle = glGetAttribLocation(shaderProgram, "iNormal");
	sSunHandle = glGetUniformLocation(shaderProgram, "uSunDirection");
	sMVPHandle = glGetUniformLocation(shaderProgram, "uMVP");
	sNormalMatrixHandle = glGetUniformLocation(shaderProgram, "uNormalMatrix");

	ModelData data = ShaderUtil::loadModel("pole");

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

//==============================================================================
// Draws Model
//==============================================================================
void Pole::draw(Camera& camera, Sun& sun) {

	//------------------------------------------------------------------------------
	// Create Model Matrix
	//------------------------------------------------------------------------------
	Matrix4f model = GLMath::getTranslation(position.x, position.y, position.z);

	//------------------------------------------------------------------------------
	// Create ModelView Matrix
	//------------------------------------------------------------------------------
	Matrix4f modelView = camera.getView() * model;

	//------------------------------------------------------------------------------
	// Create MVP Matrix
	//------------------------------------------------------------------------------
	Matrix4f MVP = camera.getProjection() * modelView;

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
	glUniform3f(sSunHandle, sun.getPosition().x, sun.getPosition().y, 0);

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
	glDrawArrays(GL_TRIANGLES, 0, vertCount);

	//------------------------------------------------------------------------------
	// Unbind / Disable Code
	//------------------------------------------------------------------------------
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}