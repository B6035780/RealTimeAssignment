#ifndef ROBOT_H
#define ROBOT_H

#include "Application.h"
#include "tinyxml2.h"
#include "Parser.h"
#include "Component.h"
#include <vector>
#include <algorithm>

class Robot
{
public:
	Robot();
	Robot(float _x, float _y, float _z, float rotY);
	~Robot();

	void loadResources();
	void releaseResources();
	void draw();
	void updateMatricies();
	void update();
private:

	Component* root;
	Component* pelvis;
	Component* body;
	Component* left_Shoulder;
	Component* left_Elbow;
	Component* left_Wrist;
	Component* right_Shoulder;
	Component* right_Elbow;
	Component* right_Wrist;
	Component* neck;
	Component* left_Hip;
	Component* left_Knee;
	Component* left_Ankle;
	Component* right_Hip;
	Component* right_Knee;
	Component* right_Ankle;

	std::vector<Component*> components;

	static tinyxml2::XMLDocument xmlIdle, xmlAttack, xmlDie; //Animation XML files
	
};

#endif
