#ifndef	ANIMATOR_H
#define ANIMATOR_H

#include "Component.h"
#include "tinyxml2.h"
#include "Parser.h"
#include "Animation.h"
#include <chrono>
#include <ctime>
#include <functional>

class Animator
{
public:
	Animator();
	~Animator();

	void update(std::vector<Component*> comps, float deltaTime);
	void interpolateComponent(float t, Component* c, std::vector<KeyFrame> frames);
	void play(std::string name);
	void loadAnimation(const tinyxml2::XMLDocument* file, std::vector<Component*> comps, std::string animName);
	void deleteAnimations();
	bool isSlowMotion();
private:
	float lerp(float a, float b, float i);
	std::map<std::string, Animation*> anims;	//Animations available to play
	Animation* currentlyPlayingAnim = NULL; //Animations being interpolated between
	float elapsed = 0.0f;
	float sElapsed = 0.0f;
	bool animFin = false;
};

#endif