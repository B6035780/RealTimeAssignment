#ifndef	ANIMATOR_H
#define ANIMATOR_H

#include "Component.h"
#include "tinyxml2.h"
#include "Parser.h"
#include <chrono>
#include <ctime>

#define TIME std::chrono::high_resolution_clock::now()
class Animator
{
public:
	Animator();
	~Animator();
	void updateAnimation(Component* c, float dTime);
	bool isAnimationPlaying();
	void changeAnimation(tinyxml2::XMLDocument* anim, std::vector<Component*> components);

private:
	tinyxml2::XMLDocument* animationPlaying = NULL; 
	int noOfFrames = 0;		

	float interpVal = 0;
	float deltaTime = 0;

	bool hasChanged = true;

	float lerp(float a, float b, float i);
	void setRot(Component* c, int frame_1, int frame_2, float interp);
	void setTrans(Component* c, int frame_1, int frame_2, float interp);
};

#endif