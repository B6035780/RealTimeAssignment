#ifndef PARSER_H
#define PARSER_H

#include "Application.h"
#include <iostream>
#include <fstream>

#define PARSER Parser::getParser()

class Parser
{
public:
	static Parser* getParser();
private:
	static Parser* instance;
	Parser();
};
#endif

