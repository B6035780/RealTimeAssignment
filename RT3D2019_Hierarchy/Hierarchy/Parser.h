#ifndef PARSER_H
#define PARSER_H

#include "Application.h"
#include "tinyxml2.h"
#include <iostream>
#include <fstream>

#define PARSER Parser::getParser()

class Parser
{
public:
	static Parser* getParser();
	void parseAnimationFile(tinyxml2::XMLDocument anim);
private:
	static Parser* instance;
	Parser();
};
#endif

