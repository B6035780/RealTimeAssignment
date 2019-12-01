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

void Animator::updateAnimation(Component* c)
{
	float x, y, z, speed;

	deltaTime = (std::chrono::high_resolution_clock::now() - lastFrame).count();
	lastFrame = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> d_Elapsed = lastFrame - animationStart;
	float f_Elapsed = d_Elapsed.count();
	float frameEnd = c->getRotationXKeyFrame(keyFrame).second;
	speed = 0.01f;
	//speed = 1.0f;

	if (animationPlaying != 0)
	{
		interpVal += (1 - (c->getRotationXKeyFrame(keyFrame).second - f_Elapsed) / c->getRotationXKeyFrame(keyFrame).second) * speed;
		x = lerp(c->getRot().x, c->getRotationXKeyFrame(keyFrame).first, interpVal);
		y = lerp(c->getRot().y, c->getRotationYKeyFrame(keyFrame).first, interpVal);
		z = lerp(c->getRot().z, c->getRotationZKeyFrame(keyFrame).first, interpVal);
		c->setRot(XMFLOAT4(x, y, z, 0));

		if (c->getNoOfTranslationKeyFrames() > keyFrame)
		{
			interpVal += (1 - (c->getRotationXKeyFrame(keyFrame).second - f_Elapsed) / c->getRotationXKeyFrame(keyFrame).second) * speed;
			x = lerp(c->getPos().x, c->getTranslationKeyFrame(keyFrame).first.x / 10, interpVal);
			y = lerp(c->getPos().y, c->getTranslationKeyFrame(keyFrame).first.y / 10, interpVal);
			z = lerp(c->getPos().z, c->getTranslationKeyFrame(keyFrame).first.z / 10, interpVal);
			c->setPos(XMFLOAT4(x, y, z, 0));
		}
	}

	if (interpVal >= 1.0f)
	{
		if (keyFrame + 1 == noOfFrames)
		{
			keyFrame = 0;
			animationStart = std::chrono::high_resolution_clock::now();
		}
		else
			keyFrame++;
		interpVal = 0;
	}
}

void Animator::changeAnimation(tinyxml2::XMLDocument* anim, std::vector<Component*> components)
{
	if (anim != animationPlaying)
	{
		animationPlaying = anim;
		PARSER->parseAnimationFile(anim, components);
		noOfFrames = PARSER->getNumberOfKeyFrames(anim);
		keyFrame = 0;
		animationStart = std::chrono::high_resolution_clock::now();
	}
}

bool Animator::isAnimationPlaying()
{
	if (animationPlaying != NULL)
		return true;
	else
		return false;
}

Animator::~Animator()
{
}
