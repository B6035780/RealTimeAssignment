#include "Robot.h"

tinyxml2::XMLDocument Robot::xmlIdle = NULL;
tinyxml2::XMLDocument Robot::xmlAttack = NULL;
tinyxml2::XMLDocument Robot::xmlDie = NULL;

Robot::Robot()
{
	PARSER->parseHierarchyFile("Resources/Robot/hierarchy.txt", components);
	animator = new Animator();
}

Robot::Robot(float _x, float _y, float _z, float rotY)
{
	
}

void Robot::loadResources()
{
	//Load Meshes
	std::string directory = "Resources/Robot/";
	std::string filePath;
	std::for_each(components.begin(), components.end(), [&directory, &filePath](Component* c) 
	{
		if (c->getName() != "root")
		{
			filePath = directory;
			filePath += c->getName();
			filePath += ".x";
			c->loadMesh(filePath.c_str());
		}
	});

	//Load animation files using assert checks
	assert(0 == xmlIdle.LoadFile("Resources/Animations/RobotIdleAnim.xml"));
	assert(0 == xmlAttack.LoadFile("Resources/Animations/RobotAttackAnim.xml"));
	assert(0 == xmlDie.LoadFile("Resources/Animations/RobotDieAnim.xml"));
}

void Robot::releaseResources()
{
	std::for_each(components.begin(), components.end(), [](Component* c)
	{
		if (c->getParent() != "")
		{
			c->releaseMesh();
		}
		delete c;
	});
	delete animator;
}

void Robot::draw()
{
	std::for_each(components.begin(), components.end(), [](Component* c)
	{
		//Makes sure Root isn't drawn
		if (c->getParent() != "")
		{
			Application::s_pApp->SetWorldMatrix(c->getWorldMatrix());
			c->getMesh()->Draw();
		}
	});
}

void Robot::updateMatricies(Component* c)
{
	XMMATRIX mRotX, mRotY, mRotZ, mTrans;
	Component* parent;

	std::for_each(components.begin(), components.end(), [&parent, &c](Component* comp)
	{
		if (comp->getName() == c->getParent())
			parent = comp;
	});

	if (c->getParent() != "")
	{
		mRotX = XMMatrixRotationX(XMConvertToRadians(c->getRot().x));
		mRotY = XMMatrixRotationY(XMConvertToRadians(c->getRot().y));
		mRotZ = XMMatrixRotationZ(XMConvertToRadians(c->getRot().z));
		mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&c->getPos()));

		c->setWorldMatrix(mRotZ * mRotX * mRotY * mTrans * parent->getWorldMatrix());
	}
	else
	{
		mRotX = XMMatrixRotationX(XMConvertToRadians(c->getRot().x));
		mRotY = XMMatrixRotationY(XMConvertToRadians(c->getRot().y));
		mRotZ = XMMatrixRotationZ(XMConvertToRadians(c->getRot().z));
		mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&c->getPos()));

		c->setWorldMatrix(mRotZ * mRotX * mRotY * mTrans);
	}
}

void Robot::update()
{
	deltaTime = .000000001f * (TIME - lastFrame).count();
	checkAnimationInput();

	if ( animator->isAnimationPlaying() )
		std::for_each(components.begin(), components.end(), std::bind(&Animator::updateAnimation, animator, std::placeholders::_1, deltaTime));

	std::for_each(components.begin(), components.end(), std::bind(&Robot::updateMatricies, this, std::placeholders::_1));
	lastFrame = TIME;
}

void Robot::checkAnimationInput()
{
	if (Application::s_pApp->IsKeyPressed('1'))
	{
		animator->changeAnimation(&xmlIdle, components);
	}
	else if (Application::s_pApp->IsKeyPressed('2'))
	{
		animator->changeAnimation(&xmlAttack, components);
	}
	else if (Application::s_pApp->IsKeyPressed('3'))
	{
		animator->changeAnimation(&xmlDie, components);
	}
}

Robot::~Robot()
{
}
