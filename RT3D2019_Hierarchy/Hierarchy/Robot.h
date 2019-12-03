#ifndef ROBOT_H
#define ROBOT_H

#include "Application.h"
#include "tinyxml2.h"
#include "Component.h"
#include "Animator.h"
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>

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
	std::vector<Component*> components;	
	
	static tinyxml2::XMLDocument xmlIdle, xmlAttack, xmlDie; //Animation DAE files

	Animator* animator;

	float deltaTime = 0;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastFrame;
	void updateMatricies(Component* c);
	void checkAnimationInput();	//Check if user has changed animation with 1, 2 and 3 keys
};

#endif
