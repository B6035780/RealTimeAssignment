#ifndef	ANIMATOR_H
#define ANIMATOR_H

#include "Component.h"
#include "tinyxml2.h"
#include "Parser.h"
#include <chrono>

class Animator
{
public:
	Animator();
	~Animator();
	void updateAnimation(Component* c);
	bool isAnimationPlaying();
	void changeAnimation(tinyxml2::XMLDocument* anim, std::vector<Component*> components);

private:
	tinyxml2::XMLDocument* animationPlaying = NULL; 
	int noOfFrames = 0;	
	int keyFrame = 0;	

	float interpVal = 0;
	float deltaTime = 0;

	std::chrono::time_point<std::chrono::steady_clock> animationStart;
	std::chrono::time_point<std::chrono::steady_clock> lastFrame;

	float lerp(float a, float b, float i);
};

#endif