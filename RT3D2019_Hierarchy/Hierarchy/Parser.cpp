#include "Parser.h"

Parser* Parser::instance = NULL;

Parser::Parser()
{
}

Parser* Parser::getParser()
{
	if (instance == NULL)
		instance = new Parser();

	return instance;
}

void Parser::parseAnimationFile(const tinyxml2::XMLDocument* file, std::vector<Component*> comps)
{
	const tinyxml2::XMLNode* currentAnim = file->FirstChild()->FirstChild();
	std::string animName;
	std::string compName, animType;
	bool hasSibling = true;

	while (hasSibling)
	{
		animName = currentAnim->ToElement()->Attribute("id");	//Searches for the id attr holding the animation name
		compName = animName.substr(0, animName.find("."));	//Searches for Component name, e.g root, which ends at fullstop

		std::for_each(comps.begin(), comps.end(), [&compName, &currentAnim, &animName](Component* c)	//searches for component using parsed name
		{
			if (c->getName() == compName)
			{
				parseAnimation(animName, currentAnim, c);
			}
		});

		if (currentAnim->NextSibling() == NULL)	//Exits out if there are no more animations to process
			hasSibling = false;
		else
			currentAnim = currentAnim->NextSibling();
	}

}

void Parser::parseHierarchyFile(std::string filePath, std::vector<Component*>& comps)
{
	std::fstream fs;
	std::string name, parent, temp;	//temp used to clear punctuation between variables
	XMFLOAT4 offset;
	XMFLOAT4 rot = XMFLOAT4(0, 0, 0, 0);
	float x, y, z;
	char c;	//used to check end of file

	fs.open(filePath);
	assert(fs.is_open());

	while (fs.get(c))
	{
		fs >> name;
		name = name.substr(0, name.size() - 1);	//Get rid of /" chars in name
		fs >> parent;
		parent = parent.substr(1, parent.size() - 2);
		fs >> x >> temp; 
		fs >> y >> temp; 
		fs >> z;

		offset = XMFLOAT4(x / 10, y / 10, z / 10, 0);
		comps.push_back(new Component(offset, rot, parent, name));
		fs.get(c);
	}
}

void Parser::parseAnimation(const std::string& animName, const tinyxml2::XMLNode* currentAnim, Component* comp)
{
	std::string animType = animName.substr(animName.find(".") + 1, animName.length()); //Searches for animation type, e.g translate, which starts at fullstop in animName
	const tinyxml2::XMLNode* animSource = currentAnim->FirstChild(); //points to input array data. Next sibling is output array
	int frameCount, counter;
	float time, x, y, z; //used as temp variables for extracting data from sstream and passing to components
	std::stringstream times, data, temp;
	
	times << animSource->FirstChild()->ToElement()->GetText(); //extracts times for frames
	temp << animSource->FirstChild()->ToElement()->Attribute("count"); //Puts keyFrame count into sstream for converting to int(for loop condition)
	temp >> frameCount;
	data << animSource->NextSibling()->FirstChild()->ToElement()->GetText(); //extracts transformation data

	if (animType == "translate")	//switch-like statement that checks animType
	{
		for (int i = 0; i < frameCount; ++i)	
		{
			times >> time;
			data >> x >> y >> z;
			comp->addTranslationKeyFrame(std::make_pair(XMFLOAT4(x, y, z, 0), time));
		}
	}
	else if (animType == "rotateX")
	{
		for (int i = 0; i < frameCount; ++i)
		{
			times >> time;
			data >> x;
			comp->addRotationXKeyFrame(std::make_pair(x, time));
		}
	}
	else if (animType == "rotateY")
	{
		for (int i = 0; i < frameCount; ++i)
		{
			times >> time;
			data >> y;
			comp->addRotationYKeyFrame(std::make_pair(y, time));
		}
	}
	else if (animType == "rotateZ")
	{
		for (int i = 0; i < frameCount; ++i)
		{
			times >> time;
			data >> z;
			comp->addRotationZKeyFrame(std::make_pair(z, time));
		}
	}
	else if (animType == "visibility")
	{
		
	}
}

int Parser::getNumberOfKeyFrames(const tinyxml2::XMLDocument* file)	//Finds total num of keyframes in animation, by comparing frame count of every component
{
	int num(0), temp;
	const tinyxml2::XMLNode* animRoot = file->FirstChild()->FirstChild();
	const tinyxml2::XMLElement* anim = animRoot->FirstChild()->FirstChild()->ToElement();
	std::stringstream ss;
	bool hasSibling = true;

	while (hasSibling)
	{
		ss << anim->Attribute("count");
		ss >> temp;

		if ( num < temp )
		{ 
			num = temp;
		}

		if (animRoot->NextSibling() == NULL)	//Exits out if there are no more animations to process
			hasSibling = false;
		else
		{
			animRoot = animRoot->NextSibling();
			anim = animRoot->FirstChild()->FirstChild()->ToElement();
			CLEAR(ss);
		}
	}

	return num;
}

void Parser::deleteParser()
{
	delete instance;
}