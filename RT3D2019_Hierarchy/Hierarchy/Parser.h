#ifndef PARSER_H
#define PARSER_H

#include "Application.h"
#include "tinyxml2.h"
#include "Component.h"
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
	static void parseAnimationFile(tinyxml2::XMLDocument* file, std::vector<Component*> comps);
private:
	static Parser* instance;
	const static tinyxml2::XMLDocument* workingFile;
	static void parseAnimation(const std::string& animName, const tinyxml2::XMLNode* currentAnim, Component* comp);

	Parser();
};
#endif

