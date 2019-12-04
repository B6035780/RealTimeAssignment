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

void Animator::play(std::string name, int trackNo)	//If trackNo == -1, play on all tracks
{
	assert(tracks.size() > 0); 
	Track* t;
	if (trackNo != -1)
	{
		//assert(trackNo > tracks.size());
		t = tracks[trackNo];
		bool isAlreadyPlaying = false;

		for (int i = 0; i < t->playingAnims.size(); i++)	//Check if animation is already playing
		{
			if (t->playingAnims[i] == *anims[name])
				isAlreadyPlaying = true;
		}

		if (!isAlreadyPlaying)
			t->playingAnims.push_back(*anims[name]);
	}
	else
	{
		for (int i = 0; i < tracks.size(); ++i)
		{
			t = tracks[i];
			bool isAlreadyPlaying = false;
			for (int i = 0; i < t->playingAnims.size(); i++)	
			{
				if (t->playingAnims[i] == *anims[name])
					isAlreadyPlaying = true;
			}

			if (!isAlreadyPlaying)
				t->playingAnims.push_back(*anims[name]);
		}
	}
}

void Animator::update(std::vector<Component*> comps, float deltaTime)
{
	sElapsed += deltaTime;	

	std::for_each(tracks.begin(), tracks.end(), std::bind(&Animator::updateTrack, this, deltaTime, std::placeholders::_1));

	for (int i = 0; i < comps.size(); ++i)	
	{
		if (comps[i]->getName() != "root")
		{
			Track* t = tracks[comps[i]->getAnimationTrack()];	//Check which track the component is attached to

			for (int j = 0; j < t->playingAnims.size(); ++j)	//If more than one animation is playing on a track blend between them
			{
				interpolateComponent(comps[i], t->playingAnims[j]);

				if (j != 0)
				{
					finalPos = XMVectorLerp(finalPos, workingPos, t->blendFactor);	//Blend final pos & rot with result of previous animation lerp
					finalRot = XMVectorLerp(finalRot, workingRot, t->blendFactor);	//Else set to working pos & rot
				}
				else
				{
					finalPos = workingPos;
					finalRot = workingRot;
				}
			}
			XMFLOAT4 temp;

			XMStoreFloat4(&temp, finalPos);	//Set final transformation data after blending
			comps[i]->setPos(temp);

			XMStoreFloat4(&temp, finalRot);
			comps[i]->setRot(temp);
		}
	}

	for (int k = 0; k < tracks.size(); ++k)
	{
		std::for_each(tracks[k]->playingAnims.begin(), tracks[k]->playingAnims.end(), [](Animation& a)
		{
			if (a.animFin &&
				a.getIsRepeating())
			{
				a.elapsed = 0.0f;
				a.animFin = false;
			}
		});
	}

	if (sElapsed >= 1 && isSlowMotion())
		sElapsed = 0;
}

void Animator::updateTrack(float deltaTime, Track* t)
{
	if (!isSlowMotion())	//check if slow mo key is down. If so, don't increment elapsed time until 1 second has passed
	{
		std::for_each(t->playingAnims.begin(), t->playingAnims.end(), [&deltaTime](Animation& a)
		{
			a.elapsed += deltaTime;
		});

		if (t->playingAnims.size() != 1)
		{
			if (t->blendFactor < 1.0f)
				t->blendFactor += t->blendSpeed;
			else
			{
				t->blendFactor = 0;
				while (t->playingAnims.size() != 1)
					t->playingAnims.erase(t->playingAnims.begin());
			}
		}
	}

	if (sElapsed >= 1 && isSlowMotion())
	{
		std::for_each(t->playingAnims.begin(), t->playingAnims.end(), [&deltaTime](Animation& a)
		{
			a.elapsed += deltaTime;
		});

		if (t->playingAnims.size() != 1)
		{
			if (t->blendFactor < 1.0f)
				t->blendFactor += t->blendSpeed;
			else
			{
				t->blendFactor = 0;
				t->playingAnims.erase(t->playingAnims.begin());
			}
		}
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

void Animator::releaseResources()
{
	std::for_each(anims.begin(), anims.end(), [](std::pair<std::string, Animation*> a)
	{
		delete a.second;
	});

	std::for_each(tracks.begin(), tracks.end(), [](Track* t)
	{
		delete t;
	});
}

void Animator::initTracks(std::vector<Component*> comps)
{
	int noOfTracks = 1;
	for (int i = 0; i < comps.size(); ++i)	//Check animTrack of every component to see how many tracks are needed
	{
		if (noOfTracks <= comps[i]->getAnimationTrack())
			noOfTracks = comps[i]->getAnimationTrack() + 1;
	}
	
	for (int j = 0; j < noOfTracks; ++j)
	{
		tracks.push_back(new Track());
	}
}

Animator::~Animator()
{
}
