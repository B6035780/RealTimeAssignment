#ifndef ROBOT_H
#define ROBOT_H

#include "Application.h"

class Robot
{
public:
	Robot();
	Robot(float _x, float _y, float _z, float rotY);
	~Robot();

	static void loadResources();
	static void releaseResources();
	void draw();
	void updateMatricies();
	void update();
private:

	static CommonMesh* s_pBodyMesh; // Only one mesh for all instances
	static CommonMesh* s_pLeft_AnkleMesh;
	static CommonMesh* s_pLeft_ElbowMesh; 
	static CommonMesh* s_pLeft_HipMesh;
	static CommonMesh* s_pLeft_KneeMesh;
	static CommonMesh* s_pLeft_ShoulderMesh;
	static CommonMesh* s_pLeft_WristMesh;
	static CommonMesh* s_pNeckMesh;
	static CommonMesh* s_pPelvisMesh;
	static CommonMesh* s_pRight_AnkleMesh;
	static CommonMesh* s_pRight_ElbowMesh;
	static CommonMesh* s_pRight_HipMesh;
	static CommonMesh* s_pRight_KneeMesh;
	static CommonMesh* s_pRight_ShoulderMesh;
	static CommonMesh* s_pRight_WristMesh;
	
	XMFLOAT4 m_v4Rot; // Euler rotation angles
	XMFLOAT4 m_v4Pos; // World position

	XMMATRIX m_mWorldTrans; // World translation matrix
	XMMATRIX m_mWorldMatrix; // World transformation matrix

	XMFLOAT4 m_v4BodyRot;
	XMFLOAT4 m_v4BodyOff;
	XMMATRIX m_mBodyWorldMatrix;

	XMFLOAT4 m_v4Left_AnkleRot;
	XMFLOAT4 m_v4Left_AnkleOff;
	XMMATRIX m_mLeft_AnkleWorldMatrix;

	XMFLOAT4 m_v4Left_ElbowRot;
	XMFLOAT4 m_v4Left_ElbowOff;
	XMMATRIX m_mLeft_ElbowWorldMatrix;

	XMFLOAT4 m_v4Left_HipRot;
	XMFLOAT4 m_v4Left_HipOff;
	XMMATRIX m_mLeft_HipWorldMatrix;

	XMFLOAT4 m_v4Left_KneeRot;
	XMFLOAT4 m_v4Left_KneeOff;
	XMMATRIX m_mLeft_KneeWorldMatrix;

	XMFLOAT4 m_v4Left_ShoulderRot;
	XMFLOAT4 m_v4Left_ShoulderOff;
	XMMATRIX m_mLeft_ShoulderWorldMatrix;

	XMFLOAT4 m_v4Left_WristRot;
	XMFLOAT4 m_v4Left_WristOff;
	XMMATRIX m_mLeft_WristWorldMatrix;

	XMFLOAT4 m_v4NeckRot;
	XMFLOAT4 m_v4NeckOff;
	XMMATRIX m_mNeckWorldMatrix;

	XMFLOAT4 m_v4PelvisRot;
	XMFLOAT4 m_v4PelvisOff;
	XMMATRIX m_mPelvisWorldMatrix;

	XMFLOAT4 m_v4Right_AnkleRot;
	XMFLOAT4 m_v4Right_AnkleOff;
	XMMATRIX m_mRight_AnkleWorldMatrix;

	XMFLOAT4 m_v4Right_ElbowRot;
	XMFLOAT4 m_v4Right_ElbowOff;
	XMMATRIX m_mRight_ElbowWorldMatrix;

	XMFLOAT4 m_v4Right_HipRot;
	XMFLOAT4 m_v4Right_HipOff;
	XMMATRIX m_mRight_HipWorldMatrix;

	XMFLOAT4 m_v4Right_KneeRot;
	XMFLOAT4 m_v4Right_KneeOff;
	XMMATRIX m_mRight_KneeWorldMatrix;

	XMFLOAT4 m_v4Right_ShoulderRot;
	XMFLOAT4 m_v4Right_ShoulderOff;
	XMMATRIX m_mRight_ShoulderWorldMatrix;

	XMFLOAT4 m_v4Right_WristRot;
	XMFLOAT4 m_v4Right_WristOff;
	XMMATRIX m_mRight_WristWorldMatrix;
};

#endif
