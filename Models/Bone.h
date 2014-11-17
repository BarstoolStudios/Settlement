#ifndef BONE_H
#define BONE_H

class Bone;

#include <vector>
#include <string>
#include <Util/GLMath.h>

class Bone {

	std::vector<Bone*> children;

	Bone* parent;

	std::string name;

	int ID;

	float length;

	Vector3f head, tail, rotation, translation;

public:

	Bone(std::string name, int ID, float length, Vector3f head, Vector3f tail, Bone* parent);

	~Bone();

	Bone* getParent();

	void setParent(Bone* parent);

	void addChild(Bone* child);

	std::vector<Bone*>* getChildren();

	std::string getName();

	int getID();

	Vector3f getRotation();

	void addRotation(Vector3f delta);

	void addTranslation(Vector3f delta);

	float getLenth();

	Vector3f getInitialHead();

	Vector3f getInitialTail();

	void setCurrentHead(Vector3f newHead);

	Vector3f getCurrentHead();

	Vector3f getCurrentTail();

	Matrix4f getMatrix();

};

#endif