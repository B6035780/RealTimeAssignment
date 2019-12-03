#include "Animator.h"



Animator::Animator()
{
}

bool Animator::isSlowMotion() const
{
	if (Application::s_pApp->IsKeyPressed('S'))
		return true;
	return false;
}

void Animator::play(std::string name)
{
	bool isAlreadyPlaying = false;

	for (int i = 0; i < playingAnims.size(); i++)	//Check if animation is already playing
	{
		//if (playingAnims[i].compare(*anims[name]))
			isAlreadyPlaying = true;
	}

	if (!isAlreadyPlaying)
		playingAnims.push_back(*anims[name]);
}

void Animator::update(std::vector<Component*> comps, float deltaTime)
{
	if (playingAnims.size() != 0)	//Check if animations are playing
	{
		sElapsed += deltaTime;	//increment slowmo counter

		if (!isSlowMotion())	//check if slow mo key is down. If so, don't increment elapsed time until 1 second has passed
		{
			std::for_each(playingAnims.begin(), playingAnims.end(), [&deltaTime](Animation a)
			{
				a.elapsed += deltaTime;
			});

			if (playingAnims.size() != 1)	//If slow mo is active, blend factor is incremented once every second as well
			{
				if (blendFactor < 1.0f)	//If blendfactor reaches 1, reset it and remove animation from track, else increment it
					blendFactor += blendSpeed;
				else
				{
					blendFactor = 0;
					playingAnims.front().elapsed = 0;
					playingAnims.front().animFin = false;
					playingAnims.erase(playingAnims.begin());
				}
			}
		}

		if (sElapsed >= 1 && isSlowMotion())	
		{
			std::for_each(playingAnims.begin(), playingAnims.end(), [&deltaTime](Animation a)
			{
				a.elapsed += deltaTime;
			});

			if (playingAnims.size() != 1)
			{
				if (blendFactor < 1.0f)
					blendFactor += blendSpeed;
				else
				{
					blendFactor = 0;
					playingAnims.front().elapsed = 0;
					playingAnims.front().animFin = false;
					playingAnims.erase(playingAnims.begin());
				}
			}

			sElapsed = 0;
		}

		for (int i = 0; i < comps.size(); ++i)	
		{
			for (int j = 0; j < playingAnims.size(); ++j)	//If more than one animation is playing blend between them
			{
				interpolateComponent(comps[i], playingAnims[j]);
				if (j != 0)
				{
					finalPos = XMVectorLerp(finalPos, workingPos, blendFactor);
					finalRot = XMVectorLerp(finalRot, workingRot, blendFactor);
				}
				else
				{
					finalPos = workingPos;
					finalRot = workingRot;
				}
			}
			XMFLOAT4 temp;

			XMStoreFloat4(&temp, finalPos);
			comps[i]->setPos(temp);

			XMStoreFloat4(&temp, finalRot);
			comps[i]->setRot(temp);
		}

		std::for_each(playingAnims.begin(), playingAnims.end(), [](Animation a)
		{
			if (a.animFin)
			{
				a.elapsed = 0.0f;
				a.animFin = false;
			}
		});
	}
}

void Animator::interpolateComponent(Component* c, Animation& a)
{
	float x, y, z, t;
	std::vector<KeyFrame> frames = a.getKeyFrames(c->getName());
	t = a.elapsed;

	if (t <= frames[0].time)	//if time is before anim start
	{
		workingPos = XMLoadFloat4(&frames[0].trans);
		x = frames[0].xRot;
		y = frames[0].yRot;
		z = frames[0].zRot;
		workingRot = XMLoadFloat4(&XMFLOAT4(x, y, z, 0));
	}
	else if (t >= frames.back().time)	//if time is after anim end
	{
		workingPos = XMLoadFloat4(&frames.back().trans);
		x = frames.back().xRot;
		y = frames.back().yRot;
		z = frames.back().zRot;
		workingRot = XMLoadFloat4(&XMFLOAT4(x, y, z, 0));
		a.animFin = true;
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
				
				workingPos = v_trans;

				workingRot = v_rot;
			}
		}
	}
}

void Animator::loadAnimation(const tinyxml2::XMLDocument* file, std::vector<Component*> comps, std::string animName)
{
	anims[animName] = (PARSER->parseAnimationFile(file, comps, animName));
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
