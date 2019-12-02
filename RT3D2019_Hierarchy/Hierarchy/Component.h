#ifndef COMPONENT_H
#define COMPONENT_H

#include "Application.h"

__declspec(align(16)) class Component
{
public:
	Component();
	Component(XMFLOAT4 pos, XMFLOAT4 rot, std::string par, std::string nombre);
	~Component();
	
	inline CommonMesh* getMesh() const { return s_pMesh; }
	inline XMMATRIX getWorldMatrix() const { return m_mWorldMatrix; }
	inline XMFLOAT4 getRot() const { return m_v4Rot; }
	inline XMFLOAT4 getPos() const { return m_v4Pos; }
	inline std::string getParent() const { return parent; }
	inline std::string getName() const { return name; }

	inline void setWorldMatrix(XMMATRIX m) { m_mWorldMatrix = m; }
	inline void setRot(XMFLOAT4 rot) { m_v4Rot = rot; }
	inline void setPos(XMFLOAT4 pos) { m_v4Pos = pos; }

	void loadMesh(const char* filePath);
	void releaseMesh();

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
private:
	CommonMesh* s_pMesh;

	XMFLOAT4 m_v4Rot;
	XMFLOAT4 m_v4Pos;
	XMMATRIX m_mWorldMatrix;

	const std::string name; //Used for parsing
	const std::string parent;
};
#endif

