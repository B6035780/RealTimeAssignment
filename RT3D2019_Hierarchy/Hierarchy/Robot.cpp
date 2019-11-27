#include "Robot.h"


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

bool Robot::s_bResourcesReady = false;

Robot::Robot()
{
}

Robot::Robot(float _x, float _y, float _z, float rotY)
{
	m_v4Pos = XMFLOAT4(_x, _y, _z, 0.0f);
	m_v4Rot = XMFLOAT4(0.0f, rotY, 0.0f, 0.0f);
}

void Robot::loadResources()
{
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
}

void Robot::draw()
{
	Application::s_pApp->SetWorldMatrix(m_mWorldMatrix);
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

	m_mWorldMatrix = mRotZ * mRotY * mRotX * mTrans;

	//calculate Pelvis
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4PelvisRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4PelvisRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4PelvisRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4PelvisOff));

	m_mPelvisWorldMatrix = mRotZ * mRotY * mRotX * mTrans * m_mWorldMatrix;

	//calculate Body
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4BodyRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4BodyRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4BodyRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4BodyOff));

	m_mBodyWorldMatrix = mRotZ * mRotY * mRotX * mTrans * m_mPelvisWorldMatrix;

	//calculate Left Shoulder
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Left_ShoulderRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Left_ShoulderRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Left_ShoulderRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Left_ShoulderOff));

	m_mLeft_ShoulderWorldMatrix = mRotZ * mRotY * mRotX * mTrans * m_mBodyWorldMatrix;

	//calculate Left Elbow
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Left_ElbowRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Left_ElbowRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Left_ElbowRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Left_ElbowOff));

	m_mLeft_ElbowWorldMatrix = mRotZ * mRotY * mRotX * mTrans * m_mLeft_ShoulderWorldMatrix;

	//calculate Left Wrist
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Left_WristRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Left_WristRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Left_WristRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Left_WristOff));

	m_mLeft_WristWorldMatrix = mRotZ * mRotY * mRotX * mTrans * m_mLeft_ElbowWorldMatrix;

	//calculate Right Shoulder
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Right_ShoulderRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Right_ShoulderRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Right_ShoulderRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Right_ShoulderOff));

	m_mRight_ShoulderWorldMatrix = mRotZ * mRotY * mRotX * mTrans * m_mBodyWorldMatrix;

	//calculate Right Elbow
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Right_ElbowRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Right_ElbowRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Right_ElbowRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Right_ElbowOff));

	m_mRight_ElbowWorldMatrix = mRotZ * mRotY * mRotX * mTrans * m_mRight_ShoulderWorldMatrix;

	//calculate Left Wrist
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Right_WristRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Right_WristRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Right_WristRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Right_WristOff));

	m_mRight_WristWorldMatrix = mRotZ * mRotY * mRotX * mTrans * m_mRight_ElbowWorldMatrix;

	//calculate Neck
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4NeckRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4NeckRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4NeckRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4NeckOff));

	m_mNeckWorldMatrix = mRotZ * mRotY * mRotX * mTrans * m_mBodyWorldMatrix;

	//left Hip
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Left_HipRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Left_HipRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Left_HipRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Left_HipOff));

	m_mLeft_HipWorldMatrix = mRotZ * mRotY * mRotX * mTrans * m_mWorldMatrix;

	//left Knee
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Left_KneeRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Left_KneeRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Left_KneeRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Left_KneeOff));

	m_mLeft_KneeWorldMatrix = mRotZ * mRotY * mRotX * mTrans * m_mLeft_HipWorldMatrix;

	//left Ankle
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Left_AnkleRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Left_AnkleRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Left_AnkleRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Left_AnkleOff));

	m_mLeft_AnkleWorldMatrix = mRotZ * mRotY * mRotX * mTrans * m_mLeft_AnkleWorldMatrix;

	//right Hip
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Right_HipRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Right_HipRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Right_HipRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Right_HipOff));

	m_mRight_HipWorldMatrix = mRotZ * mRotY * mRotX * mTrans * m_mWorldMatrix;

	//right knee
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Right_KneeRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Right_KneeRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Right_KneeRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Right_KneeOff));

	m_mRight_KneeWorldMatrix = mRotZ * mRotY * mRotX * mTrans * m_mRight_HipWorldMatrix;

	//right ankle
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Right_AnkleRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Right_AnkleRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Right_AnkleRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Right_AnkleOff));

	m_mRight_AnkleWorldMatrix = mRotZ * mRotY * mRotX * mTrans * m_mRight_AnkleWorldMatrix;
}

Robot::~Robot()
{
}
