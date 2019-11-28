#include "Parser.h"

Parser* Parser::instance = 0;

Parser::Parser()
{
}


Parser* Parser::getParser()
{
	if (instance == 0)
		instance = new Parser();

	return instance;
}

void parseAnimationFile(tinyxml2::XMLDocument anim)
{


}