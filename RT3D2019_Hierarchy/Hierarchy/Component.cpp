#include "Component.h"



Component::Component()
{
}

Component::Component(XMFLOAT4 pos, XMFLOAT4 rot, Component* par, std::string nombre)
	:	m_v4Rot(rot), m_v4Pos(pos), parent(par), name(nombre)
{

}

Component::~Component()
{
}

void Component::loadMesh(const char* filePath)
{
	s_pMesh = CommonMesh::LoadFromXFile(Application::s_pApp, filePath);
}


void Component::releaseMesh()
{
	delete s_pMesh;
}