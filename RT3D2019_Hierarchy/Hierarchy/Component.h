#ifndef COMPONENT_H
#define COMPONENT_H

#include "Application.h"

__declspec(align(16)) class Component
{
public:
	Component();
	Component(XMFLOAT4 pos, XMFLOAT4 rot, Component* par);
	~Component();
	
	inline CommonMesh* getMesh() const { return s_pMesh; }
	inline XMMATRIX getWorldMatrix() const { return m_mWorldMatrix; }
	inline XMFLOAT4 getRot() const { return m_v4Rot; }
	inline XMFLOAT4 getPos() const { return m_v4Pos; }
	inline Component* getParent() const { return parent; }

	inline void setWorldMatrix(XMMATRIX m) { m_mWorldMatrix = m; }
	inline void setRot(XMFLOAT4 rot) { m_v4Rot = rot; }
	inline void setPos(XMFLOAT4 pos) { m_v4Pos = pos; }

	void loadMesh(const char* filePath);
	void releaseMesh();
private:
	CommonMesh* s_pMesh;
	Component* parent;

	XMFLOAT4 m_v4Rot;
	XMFLOAT4 m_v4Pos;
	XMMATRIX m_mWorldMatrix;
};
#endif

