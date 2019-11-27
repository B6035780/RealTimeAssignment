#include "Robot.h"
#include <cassert>

CommonMesh* Robot::s_pBodyMesh = NULL; 
CommonMesh* Robot::s_pLeft_AnkleMesh = NULL;
CommonMesh* Robot::s_pLeft_ElbowMesh = NULL;
CommonMesh* Robot::s_pLeft_HipMesh = NULL;
CommonMesh* Robot::s_pLeft_KneeMesh = NULL;
CommonMesh* Robot::s_pLeft_ShoulderMesh = NULL;
CommonMesh* Robot::s_pLeft_WristMesh = NULL;
CommonMesh* Robot::s_pNeckMesh = NULL;
CommonMesh* Robot::s_pPelvisMesh = NULL;
CommonMesh* Robot::s_pRight_AnkleMesh = NULL;
CommonMesh* Robot::s_pRight_ElbowMesh = NULL;
CommonMesh* Robot::s_pRight_HipMesh = NULL;
CommonMesh* Robot::s_pRight_KneeMesh = NULL;
CommonMesh* Robot::s_pRight_ShoulderMesh = NULL;
CommonMesh* Robot::s_pRight_WristMesh = NULL;

tinyxml2::XMLDocument Robot::xmlIdle = NULL;

Robot::Robot()
{
}

Robot::Robot(float _x, float _y, float _z, float rotY)
{
	//initialise Offsets and rotations
	m_v4Pos = XMFLOAT4(_x, _y, _z, 0.0f);
	m_v4Rot = XMFLOAT4(0.0f, rotY, 0.0f, 0.0f);
	
	m_v4PelvisOff = XMFLOAT4(-0.0250011f, 1.525f, -0.0000005, 0.0f);
	m_v4PelvisRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_v4BodyOff = XMFLOAT4(0.0500099f, 4.3749992f, 0.0000003f, 0.0f);
	m_v4BodyRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_v4Left_ShoulderOff = XMFLOAT4(4.6f, 0.0f, -0.0009992f, 0.0f);
	m_v4Left_ShoulderRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_v4Left_ElbowOff = XMFLOAT4(3.4250019f, -0.0499817f, -0.0004262f, 0.0f);
	m_v4Left_ElbowRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_v4Left_WristOff = XMFLOAT4(5.5250008f, -0.0999710f, 0.0003968f, 0.0f);
	m_v4Left_WristRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_v4Right_ShoulderOff = XMFLOAT4(-4.4500023f, 0.0500000f, -0.000021f, 0.0f);
	m_v4Right_ShoulderRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	
	m_v4Right_ElbowOff = XMFLOAT4(-3.3999996f, 0.0250229f, -0.0000194f, 0.0f);
	m_v4Right_ElbowRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	
	m_v4Right_WristOff = XMFLOAT4(-6.0000381f, -0.1750183f, 0.0007156f, 0.0f);
	m_v4Right_WristRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_v4NeckOff = XMFLOAT4(0.0249983f, 3.6625015f, 2.5999998f, 0.0f);
	m_v4NeckRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_v4Left_HipOff = XMFLOAT4(1.9500000f, -0.7724991f, 0.000000f, 0.0f);
	m_v4Left_HipRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_v4Left_KneeOff = XMFLOAT4(0.0000006f, -2.2200001f, 0.000000f, 0.0f);
	m_v4Left_KneeRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_v4Left_AnkleOff = XMFLOAT4(-0.0800152f, -3.6399994f, -0.0000098f, 0.0f);
	m_v4Left_AnkleRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_v4Right_HipOff = XMFLOAT4(-1.9500000f, -0.7724991, 0.000000f, 0.0f);
	m_v4Right_HipRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_v4Right_KneeOff = XMFLOAT4(0.0000006f, -2.2000000f, 0.000000f, 0.0f);
	m_v4Right_KneeRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_v4Right_AnkleOff = XMFLOAT4(0.0199911f, -3.6799995f, 0.000039f, 0.0f);
	m_v4Right_AnkleRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
}

void Robot::loadResources()
{
	//Load Meshes
	s_pBodyMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Robot/body.x");
	s_pLeft_AnkleMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Robot/left_ankle.x");
	s_pLeft_ElbowMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Robot/left_elbow.x");
	s_pLeft_HipMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Robot/left_hip.x");
	s_pLeft_KneeMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Robot/left_knee.x");
	s_pLeft_ShoulderMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Robot/left_shoulder.x");
	s_pLeft_WristMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Robot/left_wrist.x");
	s_pNeckMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Robot/neck.x");
	s_pPelvisMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Robot/pelvis.x");
	s_pRight_AnkleMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Robot/right_ankle.x");
	s_pRight_ElbowMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Robot/right_elbow.x");
	s_pRight_HipMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Robot/right_hip.x");
	s_pRight_KneeMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Robot/right_knee.x");
	s_pRight_ShoulderMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Robot/right_shoulder.x");
	s_pRight_WristMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Robot/right_wrist.x");

	//Load animation files using assert checks
	assert(0 == xmlIdle.LoadFile("Resources/Animations/RobotIdleAnim.xml"));
	assert(0 == xmlIdle.LoadFile("Resources/Animations/RobotAttackAnim.xml"));
	assert(0 == xmlIdle.LoadFile("Resources/Animations/RobotDieAnim.xml"));
}

void Robot::releaseResources()
{
	delete s_pBodyMesh;
	delete s_pLeft_AnkleMesh;
	delete s_pLeft_ElbowMesh;
	delete s_pLeft_HipMesh;
	delete s_pLeft_KneeMesh;
	delete s_pLeft_ShoulderMesh;
	delete s_pLeft_WristMesh;
	delete s_pNeckMesh;
	delete s_pPelvisMesh;
	delete s_pRight_AnkleMesh;
	delete s_pRight_ElbowMesh;
	delete s_pRight_HipMesh;
	delete s_pRight_KneeMesh;
	delete s_pRight_ShoulderMesh;
	delete s_pRight_WristMesh;

	xmlIdle.Clear();
}

void Robot::draw()
{
	Application::s_pApp->SetWorldMatrix(m_mBodyWorldMatrix);
	s_pBodyMesh->Draw();

	Application::s_pApp->SetWorldMatrix(m_mLeft_AnkleWorldMatrix);
	s_pLeft_AnkleMesh->Draw();

	Application::s_pApp->SetWorldMatrix(m_mLeft_ElbowWorldMatrix);
	s_pLeft_ElbowMesh->Draw();

	Application::s_pApp->SetWorldMatrix(m_mLeft_HipWorldMatrix);
	s_pLeft_HipMesh->Draw();

	Application::s_pApp->SetWorldMatrix(m_mLeft_KneeWorldMatrix);
	s_pLeft_KneeMesh->Draw();

	Application::s_pApp->SetWorldMatrix(m_mLeft_ShoulderWorldMatrix);
	s_pLeft_ShoulderMesh->Draw();

	Application::s_pApp->SetWorldMatrix(m_mLeft_WristWorldMatrix);
	s_pLeft_WristMesh->Draw();

	Application::s_pApp->SetWorldMatrix(m_mNeckWorldMatrix);
	s_pNeckMesh->Draw();

	Application::s_pApp->SetWorldMatrix(m_mPelvisWorldMatrix);
	s_pPelvisMesh->Draw();

	Application::s_pApp->SetWorldMatrix(m_mRight_AnkleWorldMatrix);
	s_pRight_AnkleMesh->Draw();

	Application::s_pApp->SetWorldMatrix(m_mRight_ElbowWorldMatrix);
	s_pRight_ElbowMesh->Draw();

	Application::s_pApp->SetWorldMatrix(m_mRight_HipWorldMatrix);
	s_pRight_HipMesh->Draw();

	Application::s_pApp->SetWorldMatrix(m_mRight_KneeWorldMatrix);
	s_pRight_KneeMesh->Draw();

	Application::s_pApp->SetWorldMatrix(m_mRight_ShoulderWorldMatrix);
	s_pRight_ShoulderMesh->Draw();

	Application::s_pApp->SetWorldMatrix(m_mRight_WristWorldMatrix);
	s_pRight_WristMesh->Draw();
}

void Robot::updateMatricies()
{
	XMMATRIX mRotX, mRotY, mRotZ, mTrans;

	//calculate WorldMatrix
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Rot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Rot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Rot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Pos));

	m_mWorldMatrix = mRotZ * mRotX * mRotY * mTrans;

	//calculate Pelvis
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4PelvisRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4PelvisRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4PelvisRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4PelvisOff));

	m_mPelvisWorldMatrix = mRotZ * mRotX * mRotY * mTrans * m_mWorldMatrix;

	//calculate Body
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4BodyRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4BodyRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4BodyRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4BodyOff));

	m_mBodyWorldMatrix = mRotZ * mRotX * mRotY * mTrans * m_mPelvisWorldMatrix;

	//calculate Left Shoulder
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Left_ShoulderRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Left_ShoulderRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Left_ShoulderRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Left_ShoulderOff));

	m_mLeft_ShoulderWorldMatrix = mRotZ * mRotX * mRotY * mTrans * m_mBodyWorldMatrix;

	//calculate Left Elbow
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Left_ElbowRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Left_ElbowRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Left_ElbowRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Left_ElbowOff));

	m_mLeft_ElbowWorldMatrix = mRotZ * mRotX * mRotY * mTrans * m_mLeft_ShoulderWorldMatrix;

	//calculate Left Wrist
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Left_WristRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Left_WristRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Left_WristRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Left_WristOff));

	m_mLeft_WristWorldMatrix = mRotZ * mRotX * mRotY * mTrans * m_mLeft_ElbowWorldMatrix;

	//calculate Right Shoulder
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Right_ShoulderRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Right_ShoulderRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Right_ShoulderRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Right_ShoulderOff));

	m_mRight_ShoulderWorldMatrix = mRotZ * mRotX * mRotY * mTrans * m_mBodyWorldMatrix;

	//calculate Right Elbow
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Right_ElbowRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Right_ElbowRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Right_ElbowRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Right_ElbowOff));

	m_mRight_ElbowWorldMatrix = mRotZ * mRotX * mRotY * mTrans * m_mRight_ShoulderWorldMatrix;

	//calculate Left Wrist
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Right_WristRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Right_WristRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Right_WristRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Right_WristOff));

	m_mRight_WristWorldMatrix = mRotZ * mRotX * mRotY * mTrans * m_mRight_ElbowWorldMatrix;

	//calculate Neck
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4NeckRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4NeckRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4NeckRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4NeckOff));

	m_mNeckWorldMatrix = mRotZ * mRotX * mRotY * mTrans * m_mBodyWorldMatrix;

	//left Hip
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Left_HipRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Left_HipRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Left_HipRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Left_HipOff));

	m_mLeft_HipWorldMatrix = mRotZ * mRotX * mRotY * mTrans * m_mWorldMatrix;

	//left Knee
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Left_KneeRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Left_KneeRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Left_KneeRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Left_KneeOff));

	m_mLeft_KneeWorldMatrix = mRotZ * mRotX * mRotY * mTrans * m_mLeft_HipWorldMatrix;

	//left Ankle
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Left_AnkleRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Left_AnkleRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Left_AnkleRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Left_AnkleOff));

	m_mLeft_AnkleWorldMatrix = mRotZ * mRotX * mRotY * mTrans * m_mLeft_AnkleWorldMatrix;

	//right Hip
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Right_HipRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Right_HipRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Right_HipRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Right_HipOff));

	m_mRight_HipWorldMatrix = mRotZ * mRotX * mRotY * mTrans * m_mWorldMatrix;

	//right knee
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Right_KneeRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Right_KneeRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Right_KneeRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Right_KneeOff));

	m_mRight_KneeWorldMatrix = mRotZ * mRotX * mRotY * mTrans * m_mRight_HipWorldMatrix;

	//right ankle
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Right_AnkleRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Right_AnkleRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Right_AnkleRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Right_AnkleOff));

	m_mRight_AnkleWorldMatrix = mRotZ * mRotX * mRotY * mTrans * m_mRight_AnkleWorldMatrix;
}

void Robot::update()
{
	updateMatricies();
}

Robot::~Robot()
{
}
