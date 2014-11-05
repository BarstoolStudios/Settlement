/******************************************************************************\
* File: Bone.cpp
*
* Author: Josh Taylor
*
* Header: Bone.h
*
* Description: Bone to be used to construct a skeleton. Bones are nodes in a
*              tree data structure.
\******************************************************************************/

#include "Models/Bone.h"
#include "Util/GLMath.h"

Bone::Bone(std::string name, int ID, float length, Vector3f head, Vector3f tail, Bone* parent) 
	:
	name(name),
	ID(ID),
	length(length),
	head(head),
	tail(tail),
	parent(parent)
	{}

Bone::~Bone() {
	for(auto bone : children)
		delete bone;
}

Bone* Bone::getParent() {
	return parent;
}

void Bone::setParent(Bone* parent) {
	this->parent = parent;
}

void Bone::addChild(Bone* child) {
	children.push_back(child);
}

std::vector<Bone*>* Bone::getChildren() {
	return &children;
}

std::string Bone::getName() {
	return name;
}

int Bone::getID() {
	return ID;
}

Vector3f Bone::getRotation() {
	return rotation;
}

void Bone::addRotation(Vector3f delta) {
	rotation += delta;
}

void Bone::addTranslation(Vector3f delta) {
	translation += delta;
}

float Bone::getLenth() {
	return length;
}

Vector3f Bone::getInitialHead() {
	return head;
}

Vector3f Bone::getInitialTail() {
	return tail;
}

void Bone::setCurrentHead(Vector3f newHead) {
	translation = newHead - head;
}

Vector3f Bone::getCurrentHead() {
	return head + translation;
}

Vector3f Bone::getCurrentTail() {
	Vector3f temp = tail - head;
	Matrix3f rotationMatrix(GLMath::getRotation(rotation));
	temp = rotationMatrix * temp;
	return temp + getCurrentHead();
}

Matrix4f Bone::getMatrix() {
	Matrix4f subInitHead = GLMath::getTranslation(-head.x, -head.y, -head.z);
	Matrix4f rot = GLMath::getRotation(rotation);
	Matrix4f addCurrHead = GLMath::getTranslation(head + translation);

	return addCurrHead * (rot * subInitHead);
}