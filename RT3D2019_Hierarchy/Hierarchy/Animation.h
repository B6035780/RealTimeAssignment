#ifndef ANIMATION_H
#define ANIMATION_H
#include <map>
#include "Application.h"

struct KeyFrame
{
	float time, xRot, yRot, zRot;
	XMFLOAT4 trans;
};

class Animation
{
public:
	inline Animation() {}	//default

	inline Animation(std::map<std::string, std::vector<KeyFrame>> frames, std::string nombre)
		: keyFrames(frames), name(nombre) 
	{
		if (name == "die")
			isRepeating = false;
	}

	inline std::vector<KeyFrame> getKeyFrames(std::string componentName) const { return keyFrames.at(componentName); }
	inline std::map<std::string, std::vector<KeyFrame>> getAllFrames() const { return keyFrames; }
	inline std::string getName() const { return name; }
	inline bool getIsRepeating() const { return isRepeating; }

	float elapsed = 0;	//To-Do make private
	bool animFin = false;

	void operator=(const Animation& a)	//Couldn't pass-by-ref unless this was implemented
	{
		name = a.getName();
		keyFrames = a.getAllFrames();
		elapsed = a.elapsed;
		animFin = a.animFin;
		isRepeating = a.getIsRepeating();
	}

	bool operator==(const Animation& a)	//Can only compare animations attached to the same model, as only name is checked. 
	{
		if (name == a.getName())
			return true;
		else
			return false;
	}
private:
	std::map<std::string, std::vector<KeyFrame>> keyFrames;	//Holds all keyframes for every component, using component name as key
	bool isRepeating = true;
	std::string name;
};
#endif
