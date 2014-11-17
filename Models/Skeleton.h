#ifndef SKELETON_H
#define SKELETON_H

class Skeleton;

#include <string>
#include <fstream>
#include <vector>
#include "Models/Bone.h"

class Skeleton {
	std::string name;

	Bone* root;

	int numBones;

public:
	Skeleton(std::string name, std::ifstream& modelFile);
	Skeleton(Skeleton& skeleton);
	~Skeleton();

	Bone* copyBone(Bone* oldBone);

	std::string getName();

	Bone* getRoot();

	int getBoneID(std::string name);

	std::string getBoneName(int ID);

	Bone* getBone(int ID);

	Bone* getBone(std::string name);

	void getBoneMatrixArray(std::vector<GLfloat>& arr);

	int getNumBones();

	void rotate(std::string name, Vector3f rotation);

	void rotateDown(std::string name, Vector3f rotation);
};

#endif