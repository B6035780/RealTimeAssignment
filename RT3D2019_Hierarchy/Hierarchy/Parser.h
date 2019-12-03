#ifndef PARSER_H
#define PARSER_H

#include "Application.h"
#include "tinyxml2.h"
#include "Component.h"
#include "Animation.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#define PARSER Parser::getParser()
#define CLEAR(x) std::stringstream().swap(x) //Resets sstream

class Parser
{
public:
	static Parser* getParser();
	static void deleteParser();
	static Animation* parseAnimationFile(const tinyxml2::XMLDocument* file, std::vector<Component*> comps, std::string name);
	static void parseHierarchyFile(std::string filePath, std::vector<Component*>& comps);
	static int getNumberOfKeyFrames(const tinyxml2::XMLDocument* file);
private:
	static Parser* instance;
	static void parseAnimation(const std::string& animName, const tinyxml2::XMLNode* currentAnim, std::string compName, std::map<std::string, std::vector<KeyFrame>>& keyFrames);

	Parser();
};
#endif

