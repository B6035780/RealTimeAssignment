#include "Animator.h"



Animator::Animator()
{
}

float Animator::lerp(float a, float b, float i)
{
	if (1 < i)
		i = 1;
	return a + i * (b - a);
}

void Animator::loadAnimation(const tinyxml2::XMLDocument* file, std::vector<Component*> comps, std::string animName)
{
	anims[animName] = (PARSER->parseAnimationFile(file, comps));
}

void Animator::deleteAnimations()
{
	std::for_each(anims.begin(), anims.end(), [](std::pair<std::string, Animation*> a)
	{
		delete a.second;
	});
}

Animator::~Animator()
{
}
