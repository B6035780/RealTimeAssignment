#include "Robot.h"
#include <cassert>

tinyxml2::XMLDocument Robot::xmlIdle = NULL;
tinyxml2::XMLDocument Robot::xmlAttack = NULL;
tinyxml2::XMLDocument Robot::xmlDie = NULL;

Robot::Robot()
{
}

Robot::Robot(float _x, float _y, float _z, float rotY)
{
	//initialise Offsets and rotations
	XMFLOAT4 rot, pos;

	pos = XMFLOAT4(_x, _y, _z, 0.0f);
	rot = XMFLOAT4(0.0f, rotY, 0.0f, 0.0f);
	root = new Component(pos, rot, NULL, "root");
	components.push_back(root);
	
	pos = XMFLOAT4(-0.0250011f, 1.525f, -0.0000005, 0.0f);
	rot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	pelvis = new Component(pos, rot, root, "pelvis");
	components.push_back(pelvis);

	pos = XMFLOAT4(0.0500099f, 4.3749992f, 0.0000003f, 0.0f);
	rot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	body = new Component(pos, rot, pelvis, "body");
	components.push_back(body);

	pos = XMFLOAT4(4.6f, 0.0f, -0.0009992f, 0.0f);
	rot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	left_Shoulder = new Component(pos, rot, body, "left_shoulder");
	components.push_back(left_Shoulder);

	pos = XMFLOAT4(3.4250019f, -0.0499817f, -0.0004262f, 0.0f);
	rot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	left_Elbow = new Component(pos, rot, left_Shoulder, "left_elbow");
	components.push_back(left_Elbow);

	pos = XMFLOAT4(5.5250008f, -0.0999710f, 0.0003968f, 0.0f);
	rot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	left_Wrist = new Component(pos, rot, left_Elbow, "left_wrist");
	components.push_back(left_Wrist);

	pos = XMFLOAT4(-4.4500023f, 0.0500000f, -0.000021f, 0.0f);
	rot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	right_Shoulder = new Component(pos, rot, body, "right_shoulder");
	components.push_back(right_Shoulder);
	
	pos = XMFLOAT4(-3.3999996f, 0.0250229f, -0.0000194f, 0.0f);
	rot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	right_Elbow = new Component(pos, rot, right_Shoulder, "right_elbow");
	components.push_back(right_Elbow);
	
	pos = XMFLOAT4(-6.0000381f, -0.1750183f, 0.0007156f, 0.0f);
	rot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	right_Wrist = new Component(pos, rot, right_Elbow, "right_wrist");
	components.push_back(right_Wrist);

	pos = XMFLOAT4(0.0249983f, 3.6625015f, 2.5999998f, 0.0f);
	rot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	neck = new Component(pos, rot, body, "neck");
	components.push_back(neck);

	pos = XMFLOAT4(1.9500000f, -0.7724991f, 0.000000f, 0.0f);
	rot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	left_Hip = new Component(pos, rot, root, "left_hip");
	components.push_back(left_Hip);

	pos = XMFLOAT4(0.0000006f, -2.2200001f, 0.000000f, 0.0f);
	rot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	left_Knee = new Component(pos, rot, left_Hip, "left_knee");
	components.push_back(left_Knee);

	pos = XMFLOAT4(-0.0800152f, -3.6399994f, -0.0000098f, 0.0f);
	rot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	left_Ankle = new Component(pos, rot, left_Knee, "left_ankle");
	components.push_back(left_Ankle);

	pos = XMFLOAT4(-1.9500000f, -0.7724991, 0.000000f, 0.0f);
	rot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	right_Hip = new Component(pos, rot, root, "right_hip");
	components.push_back(right_Hip);

	pos = XMFLOAT4(0.0000006f, -2.2000000f, 0.000000f, 0.0f);
	rot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	right_Knee = new Component(pos, rot, right_Hip, "right_knee");
	components.push_back(right_Knee);

	pos = XMFLOAT4(0.0199911f, -3.6799995f, 0.000039f, 0.0f);
	rot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	right_Ankle = new Component(pos, rot, right_Knee, "right_ankle");
	components.push_back(right_Ankle);
}

void Robot::loadResources()
{
	//Load Meshes
	body->loadMesh("Resources/Robot/body.x");
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
	right_Wrist->loadMesh("Resources/Robot/right_wrist.x");

	//Load animation files using assert checks
	assert(0 == xmlIdle.LoadFile("Resources/Animations/RobotIdleAnim.xml"));
	assert(0 == xmlAttack.LoadFile("Resources/Animations/RobotAttackAnim.xml"));
	assert(0 == xmlDie.LoadFile("Resources/Animations/RobotDieAnim.xml"));
}

void Robot::releaseResources()
{
	std::for_each(components.begin(), components.end(), [](Component* c)
	{
		if (c->getParent() != NULL)
		{
			c->releaseMesh();
		}
		delete c;
	});

	xmlIdle.Clear();
	xmlAttack.Clear();
	xmlDie.Clear();
}

void Robot::draw()
{
	std::for_each(components.begin(), components.end(), [](Component* c)
	{
		//Makes sure Root isn't drawn
		if (c->getParent() != NULL)
		{
			Application::s_pApp->SetWorldMatrix(c->getWorldMatrix());
			c->getMesh()->Draw();
		}
	});
}

void Robot::updateMatricies()
{
	XMMATRIX mRotX, mRotY, mRotZ, mTrans;
	std::for_each(components.begin(), components.end(), [&mRotX, &mRotY, &mRotZ, &mTrans](Component* c)
	{
		if (c->getParent() != NULL)
		{
			mRotX = XMMatrixRotationX(XMConvertToRadians(c->getRot().x));
			mRotY = XMMatrixRotationY(XMConvertToRadians(c->getRot().y));
			mRotZ = XMMatrixRotationZ(XMConvertToRadians(c->getRot().z));
			mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&c->getPos()));

			c->setWorldMatrix( mRotZ * mRotX * mRotY * mTrans * c->getParent()->getWorldMatrix() );
		}
		else
		{
			mRotX = XMMatrixRotationX(XMConvertToRadians(c->getRot().x));
			mRotY = XMMatrixRotationY(XMConvertToRadians(c->getRot().y));
			mRotZ = XMMatrixRotationZ(XMConvertToRadians(c->getRot().z));
			mTrans = XMMatrixTranslationFromVector( XMLoadFloat4( &c->getPos() ) );

			c->setWorldMatrix(mRotZ * mRotX * mRotY * mTrans);
		}
	});

}

void Robot::update()
{
	if (checkAnimationInput() != animationPlaying)
		changeAnimation(checkAnimationInput());

	updateMatricies();
}

void Robot::changeAnimation(int anim)
{
	switch (anim)
	{
	case IDLE:
		PARSER->parseAnimationFile(&xmlIdle, components);
		break;
	case ATTACK:
		PARSER->parseAnimationFile(&xmlAttack, components);
		break;
	case DIE:
		PARSER->parseAnimationFile(&xmlDie, components);
		break;
	}
}

void Robot::updateAnimation()
{

}

int Robot::checkAnimationInput()
{
	if (Application::s_pApp->IsKeyPressed('1'))
		return 1;
	else if (Application::s_pApp->IsKeyPressed('2'))
		return 2;
	else if (Application::s_pApp->IsKeyPressed('3'))
		return 3;
	else
		return 0;
}

Robot::~Robot()
{
}
