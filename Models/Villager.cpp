/******************************************************************************\
* File: Villager.cpp
*
* Author: Josh Taylor
*
* Header: Villager.h
*
* Description: Villager Model rigged with Skeleton
\******************************************************************************/

#include "Models/Villager.h"
#include "Util/GLMath.h"
#include "Util/ShaderUtil.h"
#include "Models/ModelData.h"
#include <string>
#include "Util/GameTimer.h"
#include "Main/Camera.h"
#include "Terrain/Sun.h"

const float Villager::WALK_SPEED = 0.003f;
const float Villager::FLEE_SPEED = 0.006f;
const float Villager::ROTATION_SPEED = 0.1f;

GLuint Villager::VAO = 0;

GLint Villager::sPositionHandle = -1;
GLint Villager::sNormalHandle = -1;
GLint Villager::sSunHandle = -1;
GLint Villager::sMVPHandle = -1;
GLint Villager::sNormalMatrixHandle = -1;
GLint Villager::sBoneMatricesHandle = -1;
GLint Villager::sBoneWeightsHandle = -1;
GLint Villager::sBoneIndicesHandle = -1;

GLuint Villager::shaderProgram = 0;

GLuint Villager::verticesVBO = 0;
GLuint Villager::normalsVBO = 0;
GLuint Villager::boneWeightsVBO = 0;
GLuint Villager::boneIndicesVBO = 0;

int Villager::vertCount = -1;

Skeleton* Villager::baseSkeleton = NULL;

Villager::Villager(Vector3f position) : position(position) {
	skeleton = new Skeleton(*baseSkeleton);
}

Villager::~Villager() {
	delete skeleton;
}

void Villager::loadResources() {

	ModelData data = ShaderUtil::loadModel("villager");


	verticesVBO = data.getVerticesVBO();
	normalsVBO = data.getNormalsVBO();
	boneWeightsVBO = data.getBoneWeightsVBO();
	boneIndicesVBO = data.getBoneIndicesVBO();

	vertCount = data.getVertCount();

	baseSkeleton = data.getSkeleton();

	std::vector<GLenum> shadersUsed {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
	shaderProgram = ShaderUtil::createProgram("Villager", shadersUsed, true);

	sMVPHandle = glGetUniformLocation(shaderProgram, "uMVP");
	sSunHandle = glGetUniformLocation(shaderProgram, "uSunDirection");
	sNormalMatrixHandle = glGetUniformLocation(shaderProgram, "uNormalMatrix");
	sBoneWeightsHandle = glGetAttribLocation(shaderProgram, "iBoneWeights");
	sBoneIndicesHandle = glGetAttribLocation(shaderProgram, "iBoneIndices");
	sPositionHandle = glGetAttribLocation(shaderProgram, "iPosition");
	sNormalHandle = glGetAttribLocation(shaderProgram, "iNormal");
	sBoneMatricesHandle = glGetUniformLocation(shaderProgram, "uBoneMatrices");

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

	//------------------------------------------------------------------------------
	// Load Bone Weight Data
	//------------------------------------------------------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, boneWeightsVBO);
	glEnableVertexAttribArray(sBoneWeightsHandle);
	glVertexAttribPointer(sBoneWeightsHandle, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//------------------------------------------------------------------------------
	// Load Bone Indices Data
	//------------------------------------------------------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, boneIndicesVBO);
	glEnableVertexAttribArray(sBoneIndicesHandle);
	glVertexAttribPointer(sBoneIndicesHandle, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Villager::draw(Camera& camera, Sun& sun) {
	
	//------------------------------------------------------------------------------
	// Create Model Matrix
	//------------------------------------------------------------------------------
	Matrix4f translationMatrix = GLMath::getTranslation(position);
	Matrix4f rotationMatrix = GLMath::getRotation(0, rotation, 0);
	Matrix4f model = translationMatrix * rotationMatrix;

	//------------------------------------------------------------------------------
	// Create ModelView Matrix
	//------------------------------------------------------------------------------
	Matrix4f modelView = camera.getView() * model;

	//------------------------------------------------------------------------------
	// Create Normal Matrix
	//------------------------------------------------------------------------------
	Matrix4f temp(model);
	temp.inverse();
	temp.transpose();
	Matrix3f nMatrix(temp);

	//------------------------------------------------------------------------------
	// Create MVP Matrix
	//------------------------------------------------------------------------------
	Matrix4f MVP = camera.getProjection() * modelView;


	glBindVertexArray(VAO);

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
	// Load Bone Matrices 
	//------------------------------------------------------------------------------
	std::vector<GLfloat> arrBoneMatrices;
	skeleton->getBoneMatrixArray(arrBoneMatrices);
	glUniformMatrix4fv(sBoneMatricesHandle, skeleton->getNumBones(), GL_TRUE, &(arrBoneMatrices[0]));

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

Skeleton* Villager::getSkeleton() {
	return skeleton;
}