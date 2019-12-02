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
	inline Animation(std::map<std::string, std::vector<KeyFrame>> frames)
		: keyFrames(frames) {}
	Animation();
	~Animation();

	inline int getNumberOfKeyFrames() { return noOfKeyFrames; }
	inline std::vector<KeyFrame> getKeyFrames(std::string componentName) { return keyFrames.at(componentName); }

	inline void addKeyFrames(std::string name, std::vector<KeyFrame>) {}
private:
	int noOfKeyFrames;
	std::map<std::string, std::vector<KeyFrame>> keyFrames;	//Holds all keyframes for every component, using component name as key
};
#endif
