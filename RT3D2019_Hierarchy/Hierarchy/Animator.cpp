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

void Animator::updateAnimation(Component* c, float dTime)
{
	if (c->getName() == "root")
		deltaTime += dTime; 
	int frame_1(-1), frame_2(0);

	for (int i = 0; i < c->getNoOfRotationXKeyFrames(); ++i)
	{
		if (deltaTime >= c->getRotationXKeyFrames()[i].second)
			frame_1 = i;
	}

	if (frame_1 + 1 != c->getNoOfRotationXKeyFrames())
		frame_2 = frame_1 + 1;
	else
		frame_2 = frame_1;

	float timeDiff = c->getRotationXKeyFrames()[frame_2].second - c->getRotationXKeyFrames()[frame_1].second;
	if (timeDiff == 0.0f)
		timeDiff = 1;

	interpVal = ((deltaTime - c->getRotationXKeyFrames()[frame_1].second) / timeDiff + 0.5) * 2;

	setRot(c, frame_1, frame_2, interpVal);
	setTrans(c, frame_1, frame_2, interpVal);

	if (deltaTime >= frameEnd)
	{
		if (keyFrame + 1 == noOfFrames)
		{
			keyFrame = 0;
		}
		else
			keyFrame++;
		deltaTime = 0;
		interpVal = 0;
	}
}

void Animator::setRot(Component* c, int frame_1, int frame_2, float interpVal)
{
	float x, y, z;
	if (frame_1 != -1)
	{
		x = lerp(c->getRotationXKeyFrames()[frame_1].first, c->getRotationXKeyFrames()[frame_2].first, interpVal);
		y = lerp(c->getRotationYKeyFrames()[frame_1].first, c->getRotationYKeyFrames()[frame_2].first, interpVal);
		z = lerp(c->getRotationZKeyFrames()[frame_1].first, c->getRotationZKeyFrames()[frame_2].first, interpVal);
	}
	else
	{
		x = lerp(c->getRot().x, c->getRotationXKeyFrames()[frame_2].first, interpVal);
		y = lerp(c->getRot().y, c->getRotationYKeyFrames()[frame_2].first, interpVal);
		z = lerp(c->getRot().z, c->getRotationZKeyFrames()[frame_2].first, interpVal);
	}
	c->setRot(XMFLOAT4(x, y, z, 0));
}

void Animator::setTrans(Component* c, int frame_1, int frame_2, float interpVal)
{
	float x, y, z;

	if (c->getNoOfTranslationKeyFrames() > frame_1)
	{
		if (frame_1 == -1)
		{
			if (c->getNoOfTranslationKeyFrames() <= frame_2)
			{
				frame_2 = frame_1;
				float timeDiff = c->getRotationXKeyFrames()[frame_2].second - c->getRotationXKeyFrames()[frame_1].second;
				if (timeDiff == 0.0f)
					timeDiff = 1;

				interpVal = ((deltaTime - c->getRotationXKeyFrames()[frame_1].second) / timeDiff + 0.5) * 2;
			}
			y = lerp(c->getTranslationKeyFrames()[frame_1].first.y, c->getTranslationKeyFrames()[frame_2].first.y / 10, interpVal);
			x = lerp(c->getTranslationKeyFrames()[frame_1].first.x, c->getTranslationKeyFrames()[frame_2].first.x / 10, interpVal);
			z = lerp(c->getTranslationKeyFrames()[frame_1].first.z, c->getTranslationKeyFrames()[frame_2].first.z / 10, interpVal);
			c->setPos(XMFLOAT4(x, y, z, 0));
		}
	}
	else
	{
		x = lerp(c->getPos().x, c->getTranslationKeyFrames()[frame_2].first.x / 10, interpVal);
		y = lerp(c->getPos().y, c->getTranslationKeyFrames()[frame_2].first.y / 10, interpVal);
		z = lerp(c->getPos().z, c->getTranslationKeyFrames()[frame_2].first.z / 10, interpVal);
		c->setPos(XMFLOAT4(x, y, z, 0));
	}
}

void Animator::changeAnimation(tinyxml2::XMLDocument* anim, std::vector<Component*> components)
{
	if (anim != animationPlaying)
	{
		animationPlaying = anim;
		PARSER->parseAnimationFile(anim, components);
		noOfFrames = PARSER->getNumberOfKeyFrames(anim);
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
