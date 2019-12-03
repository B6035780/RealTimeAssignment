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
	void interpolateComponent(Component* c, Animation* a);
	void play(std::string name);
	void loadAnimation(const tinyxml2::XMLDocument* file, std::vector<Component*> comps, std::string animName);
	void deleteAnimations();
	bool isSlowMotion() const;

private:
	std::map<std::string, Animation*> anims;	//Animations available to play
	std::vector<Animation*> playingAnims; //Animations being interpolated between

	float elapsed = 0.0f;
	float sElapsed = 0.0f;
	float blendFactor = 0.1f;
	float blendSpeed = 0.1f;

	XMVECTOR workingPos, workingRot;
	XMVECTOR finalPos, finalRot;

	bool animFin = false;
};

#endif