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
	PARSER->parseHierarchyFile("Resources/Robot/hierarchy.txt", components);
	XMFLOAT4 pos(components[0]->getPos().x + _x, components[0]->getPos().y + _y, components[0]->getPos().z + _z, 0);
	components[0]->setPos(pos);
	components[0]->setRot(XMFLOAT4(components[0]->getRot().x, rotY, components[0]->getRot().z, 0));
	animator = new Animator();
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

	//Load animation files
	assert(0 == xmlIdle.LoadFile("Resources/Anims/RobotIdleAnim.dae"));
	assert(0 == xmlAttack.LoadFile("Resources/Anims/RobotAttackAnim.dae"));
	assert(0 == xmlDie.LoadFile("Resources/Anims/RobotDieAnim.dae"));

	animator->initTracks(components);
	
	animator->loadAnimation(&xmlIdle, components, "idle");
	animator->play("idle");
	animator->loadAnimation(&xmlAttack, components, "attack");
	animator->loadAnimation(&xmlDie, components, "die");
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

	animator->releaseResources();
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
	deltaTime = .000000001f * (TIME - lastFrame).count();	//right-hand of * is delta time in nanoseconds. Left-hand converts to seconds
	checkAnimationInput();	

	animator->update(components, deltaTime);	

	std::for_each(components.begin(), components.end(), std::bind(&Robot::updateMatricies, this, std::placeholders::_1));
	lastFrame = TIME;
}

void Robot::checkAnimationInput()
{
	bool upArrowPress = Application::s_pApp->IsKeyPressed(VK_UP);
	bool downArrowPress = Application::s_pApp->IsKeyPressed(VK_DOWN);
	int trackNo = -1;	//Default value plays on every track

	if (Application::s_pApp->IsKeyPressed(VK_UP))
		trackNo = 0;
	else if (Application::s_pApp->IsKeyPressed(VK_DOWN))
		trackNo = 1;

	if (Application::s_pApp->IsKeyPressed('1'))
	{
		animator->play("idle", trackNo);
	}
	else if (Application::s_pApp->IsKeyPressed('2'))
	{
		animator->play("attack", trackNo);
	}
	else if (Application::s_pApp->IsKeyPressed('3'))
	{
		animator->play("die", trackNo);
	}
}

Robot::~Robot()
{
}
