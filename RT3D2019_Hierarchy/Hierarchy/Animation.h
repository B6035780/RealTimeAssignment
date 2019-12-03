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
	inline Animation(std::map<std::string, std::vector<KeyFrame>> frames, std::string nombre)
		: keyFrames(frames), name(nombre) {}

	inline std::vector<KeyFrame> getKeyFrames(std::string componentName) const { return keyFrames.at(componentName); }
	
	float elapsed = 0;
	bool animFin = false;
private:
	const std::map<std::string, std::vector<KeyFrame>> keyFrames;	//Holds all keyframes for every component, using component name as key
	const std::string name;
};
#endif
