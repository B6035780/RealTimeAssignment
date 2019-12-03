#ifndef	ANIMATOR_H
#define ANIMATOR_H

#include "Component.h"
#include "tinyxml2.h"
#include "Parser.h"
#include "Animation.h"
#include <chrono>
#include <ctime>
#include <functional>

struct Track
{
	float blendFactor = 0.0f;
	float blendSpeed = 0.1f;
	std::vector<Animation> playingAnims; //Animations being interpolated between
};

class Animator
{
public:
	Animator();
	~Animator();

	void update(std::vector<Component*> comps, float deltaTime);
	void play(std::string name, int trackNo = -1);
	void loadAnimation(const tinyxml2::XMLDocument* file, std::vector<Component*> comps, std::string animName);
	void releaseResources();
	void initTracks(std::vector<Component*> comps);

private:
	std::map<std::string, Animation*> anims;	//Animations available to play
	std::vector<Track*> tracks;

	float sElapsed = 0.0f;	//Slow-mo counter. Resets every second

	XMVECTOR workingPos, workingRot;	//Working rot & pos are set at the end of each animation interp 
	XMVECTOR finalPos, finalRot;		//Final pos & rot are the result of blending the result of each animation

	void interpolateComponent(Component* c, Animation& a);
	void updateTrack(float deltaTime, Track* t);
	bool isSlowMotion() const;
};

#endif