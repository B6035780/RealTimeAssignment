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

bool Animator::isSlowMotion()
{
	if (Application::s_pApp->IsKeyPressed('S'))
		return true;
	return false;
}

void Animator::play(std::string name)
{
	currentlyPlayingAnim = anims[name];
}

void Animator::update(std::vector<Component*> comps, float deltaTime)
{
	if (currentlyPlayingAnim != NULL)
	{
		sElapsed += deltaTime;
		if (!isSlowMotion())
			elapsed += deltaTime;
		if (sElapsed >= 1 && isSlowMotion())
		{
			elapsed += deltaTime;
			sElapsed = 0;
		}
		for (int i = 0; i < comps.size() - 1; ++i)
		{
			interpolateComponent(elapsed, comps[i], currentlyPlayingAnim->getKeyFrames(comps[i]->getName()));
		}
	}

	if (animFin)
	{
		elapsed = 0;
		animFin = false;
		if (currentlyPlayingAnim == anims["die"])
			currentlyPlayingAnim = NULL;
	}
}

void Animator::interpolateComponent(float t, Component* c, std::vector<KeyFrame> frames)
{
	float x, y, z;
	if (t <= frames[0].time)	//if time is before anim start
	{
		c->setPos(frames[0].trans);
		x = frames[0].xRot;
		y = frames[0].yRot;
		z = frames[0].zRot;
		c->setRot(XMFLOAT4(x, y, z, 0));
	}
	else if (t >= frames.back().time)	//if time is after anim end
	{
		c->setPos(frames.back().trans);
		x = frames.back().xRot;
		y = frames.back().yRot;
		z = frames.back().zRot;
		c->setRot(XMFLOAT4(x, y, z, 0));
		animFin = true;
	}
	else
	{
		for (int i = 0; i < frames.size() - 1; ++i)
		{
			if (t >= frames[i].time &&	//Find which two frames t lies between
				t <= frames[i + 1].time)
			{
				float lerpVal = (t - frames[i].time) / (frames[i + 1].time - frames[i].time);

				XMVECTOR t0 = XMLoadFloat4(&frames[i].trans);
				XMVECTOR t1 = XMLoadFloat4(&frames[i + 1].trans);
				XMVECTOR v_trans = XMVectorLerp(t0, t1, lerpVal);
				
				XMFLOAT4 f_r0(frames[i].xRot, frames[i].yRot, frames[i].zRot, 0);
				XMFLOAT4 f_r1(frames[i + 1].xRot, frames[i + 1].yRot, frames[i + 1].zRot, 0);
				XMVECTOR v_r0 = XMLoadFloat4(&f_r0);
				XMVECTOR v_r1 = XMLoadFloat4(&f_r1);
				XMVECTOR v_rot = XMVectorLerp(v_r0, v_r1, lerpVal);
				
				XMStoreFloat4(&f_r0, v_trans);
				c->setPos(f_r0);

				XMStoreFloat4(&f_r0, v_rot);
				c->setRot(f_r0);
			}
		}
	}
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
