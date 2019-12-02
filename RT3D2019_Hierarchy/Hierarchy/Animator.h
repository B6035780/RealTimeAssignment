#ifndef	ANIMATOR_H
#define ANIMATOR_H

#include "Component.h"
#include "tinyxml2.h"
#include "Parser.h"
#include "Animation.h"
#include <chrono>
#include <ctime>

class Animator
{
public:
	Animator();
	~Animator();

	void loadAnimation(const tinyxml2::XMLDocument* file, std::vector<Component*> comps, std::string animName);
	void deleteAnimations();
private:
	float lerp(float a, float b, float i);
	std::map<std::string, Animation*> anims;	//Animations available to play
	std::vector<Animation> currentlyPlayingAnims; //Animations being interpolated between
};

#endif