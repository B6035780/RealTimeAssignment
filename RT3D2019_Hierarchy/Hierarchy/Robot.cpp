#include "Robot.h"

tinyxml2::XMLDocument Robot::xmlIdle = NULL;
tinyxml2::XMLDocument Robot::xmlAttack = NULL;
tinyxml2::XMLDocument Robot::xmlDie = NULL;

Robot::Robot()
{
	PARSER->parseHierarchyFile("Resources/Robot/hierarchy.txt", components);
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
	/*body->loadMesh("Resources/Robot/body.x");
	left_Ankle->loadMesh("Resources/Robot/left_ankle.x");
	left_Elbow->loadMesh("Resources/Robot/left_elbow.x");
	left_Hip->loadMesh("Resources/Robot/left_hip.x");
	left_Knee->loadMesh("Resources/Robot/left_knee.x");
	left_Shoulder->loadMesh("Resources/Robot/left_shoulder.x");
	left_Wrist->loadMesh("Resources/Robot/left_wrist.x");
	neck->loadMesh("Resources/Robot/neck.x");
	pelvis->loadMesh("Resources/Robot/pelvis.x");
	right_Ankle->loadMesh("Resources/Robot/right_ankle.x");
	right_Elbow->loadMesh("Resources/Robot/right_elbow.x");
	right_Hip->loadMesh("Resources/Robot/right_hip.x");
	right_Knee->loadMesh("Resources/Robot/right_knee.x");
	right_Shoulder->loadMesh("Resources/Robot/right_shoulder.x");
	right_Wrist->loadMesh("Resources/Robot/right_wrist.x");*/

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
	checkAnimationInput();

	if ( animator.isAnimationPlaying() )
		std::for_each(components.begin(), components.end(), std::bind(&Animator::updateAnimation, animator, std::placeholders::_1));

	std::for_each(components.begin(), components.end(), std::bind(&Robot::updateMatricies, this, std::placeholders::_1));
}

void Robot::checkAnimationInput()
{
	if (Application::s_pApp->IsKeyPressed('1'))
	{
		animator.changeAnimation(&xmlIdle, components);
	}
	else if (Application::s_pApp->IsKeyPressed('2'))
	{
		animator.changeAnimation(&xmlAttack, components);
	}
	else if (Application::s_pApp->IsKeyPressed('3'))
	{
		animator.changeAnimation(&xmlDie, components);
	}
}

Robot::~Robot()
{
}
