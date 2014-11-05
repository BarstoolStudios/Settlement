/******************************************************************************\
* File: Skeleton.cpp
*
* Author: Josh Taylor
*
* Header: Skeleton.h
*
* Description: Stores a tree of bones loaded from a .bar file
\******************************************************************************/

#include "Models/Skeleton.h"
#include "Models/Bone.h"
#include "Util/ShaderUtil.h"
#include "Util/Utility.h"

Skeleton::Skeleton(std::string name, std::ifstream& modelFile) : name(name) {

	root = new Bone("root", -1, -1, Vector3f(), Vector3f(), NULL);
	int idGiver = 0;
	int prevLevel = 0;
	int currLevel = 0;
	std::string bName = "";
	float length = 0.0f;
	Vector3f head;
	Vector3f tail;
	Bone* newBone;

	numBones = 0;

	Bone* currParent = root;

	std::string line = "";
	std::getline(modelFile, line);

	while(line != "a") {
		std::vector<std::string> split;
		Utility::stringSplit(line, ' ', split);

		currLevel = split[0].size();

		bName = split[1];

		head = Vector3f(std::stof(split[2]), std::stof(split[3]), std::stof(split[4]));
		tail = Vector3f(std::stof(split[5]), std::stof(split[6]), std::stof(split[7]));

		length = std::stof(split[8]);

		if(currLevel == prevLevel) {
			currParent = currParent->getParent();
		} else if(currLevel < prevLevel) {
			int diff = (prevLevel - currLevel) + 1;
			for(int i = 0; i < diff; i++)
				currParent = currParent->getParent();
		}

		newBone = new Bone(bName, idGiver++, length, head, tail, currParent);
		currParent->addChild(newBone);
		currParent = newBone;

		prevLevel = currLevel;

		numBones++;

		std::getline(modelFile, line);
	}
}

Skeleton::Skeleton(Skeleton& skeleton) {
	name = skeleton.name;
	numBones = skeleton.numBones;
	root = new Bone("root", -1, -1, Vector3f(), Vector3f(), NULL);

	for(auto child : *(skeleton.root->getChildren()))
		root->addChild(copyBone(child));

	for(auto child : *(root->getChildren()))
		child->setParent(root);
}

Skeleton::~Skeleton() {
	delete root;
}

Bone* Skeleton::copyBone(Bone* oldBone) {
	Bone* newBone = new Bone(oldBone->getName(), oldBone->getID(), oldBone->getLenth(),
							 oldBone->getInitialHead(), oldBone->getInitialTail(), NULL);

	for(auto child : *(oldBone->getChildren()))
		newBone->addChild(copyBone(child));

	for(auto child : *(newBone->getChildren()))
		child->setParent(newBone);

	return newBone;
}

std::string Skeleton::getName() {
	return name;
}

Bone* Skeleton::getRoot() {
	return root;
}

int Skeleton::getBoneID(std::string name) {
	Bone* bone = getBone(name);

	return bone == NULL ? -1 : bone->getID();
}

std::string Skeleton::getBoneName(int ID) {
	Bone* bone = getBone(ID);

	return bone == NULL ? "" : bone->getName();
}

Bone* Skeleton::getBone(int ID) {
	std::vector<Bone*> queue;
	queue.push_back(root);

	Bone* b;

	while(queue.size() > 0) {
		b = queue[0];
		queue.erase(queue.begin());

		if(ID == b->getID())
			return b;

		queue.insert(queue.end(), b->getChildren()->begin(), b->getChildren()->end());
	}

	return NULL;
}

Bone* Skeleton::getBone(std::string name) {
	std::vector<Bone*> queue;
	queue.push_back(root);

	Bone* b;

	while(queue.size() > 0) {
		b = queue[0];
		queue.erase(queue.begin());

		if(name == b->getName())
			return b;

		queue.insert(queue.end(), b->getChildren()->begin(), b->getChildren()->end());
	}

	return NULL;
}

void Skeleton::getBoneMatrixArray(std::vector<GLfloat>& arr) {
	std::vector<Matrix4f> mats(numBones);

	std::vector<Bone*> breadth;

	breadth.insert(breadth.end(), root->getChildren()->begin(), root->getChildren()->end());

	Bone* curr = NULL;

	while(breadth.size() > 0) {
		curr = breadth[0];
		breadth.erase(breadth.begin());

		breadth.insert(breadth.end(), curr->getChildren()->begin(), curr->getChildren()->end());

		mats[curr->getID()] = curr->getMatrix();
	}

	for(auto mat : mats)
		mat.pushOn(&arr);
}

int Skeleton::getNumBones() {
	return numBones;
}

void Skeleton::rotate(std::string name, Vector3f rotation) {
	Bone* curr = getBone(name);

	if(curr == NULL) {
		Utility::printToOutput("ERROR -- " + name + " Bone Not Found");
		return;
	}

	Vector3f prevTail = curr->getCurrentTail();
	curr->addRotation(rotation);

	Vector3f newTail = curr->getCurrentTail();

	Vector3f translation = newTail - prevTail;

	// Update All Children
	std::vector<Bone*> breadth;
	breadth.insert(breadth.end(), curr->getChildren()->begin(), curr->getChildren()->end());

	while(breadth.size() > 0) {
		curr = breadth[0];

		curr->addTranslation(translation);

		breadth.erase(breadth.begin());
		breadth.insert(breadth.end(), curr->getChildren()->begin(), curr->getChildren()->end());
	}
}

void Skeleton::rotateDown(std::string name, Vector3f rotation) {
	Bone* curr = getBone(name);

	if(curr == NULL) {
		Utility::printToOutput("ERROR -- " + name + " Bone Not Found");
		return;
	}

	curr->addRotation(rotation);

	// Update All Children
	std::vector<Bone*> breadth;
	breadth.insert(breadth.end(), curr->getChildren()->begin(), curr->getChildren()->end());

	while(breadth.size() > 0) {
		curr = breadth[0];
		
		curr->addRotation(rotation);

		curr->setCurrentHead(curr->getParent()->getCurrentTail());

		breadth.erase(breadth.begin());
		breadth.insert(breadth.end(), curr->getChildren()->begin(), curr->getChildren()->end());
	}
}