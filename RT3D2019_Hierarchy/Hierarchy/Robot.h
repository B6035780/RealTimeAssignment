#ifndef ROBOT_H
#define ROBOT_H

#include "Application.h"
#include "tinyxml2.h"
#include "Parser.h"
#include "Component.h"
#include <vector>
#include <algorithm>

#define IDLE 1
#define ATTACK 2
#define DIE 3

class Robot
{
public:
	Robot();
	Robot(float _x, float _y, float _z, float rotY);
	~Robot();

	void loadResources();
	void releaseResources();
	void draw();
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

	std::vector<Component*> components;	//Holds pointers to all components, so they can easily be used in for loops
	std::vector<float> frameTimes; //Will hold all values for frame timings when parsed from animation file

	int animationPlaying = 0; //0 = None, 1 = idle, 2 = attack, 3 = die

	static tinyxml2::XMLDocument xmlIdle, xmlAttack, xmlDie; //Animation XML files

	void updateMatricies();
	void updateAnimation();
	int checkAnimationInput(); //Check if user has changed animation playing with 1, 2 and 3 keys
	void changeAnimation(int anim);
};

#endif
