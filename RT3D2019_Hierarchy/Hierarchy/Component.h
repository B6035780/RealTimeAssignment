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

 	inline void addTranslationKeyFrame(std::pair<XMFLOAT4, float> trans) { translationKeyFrames.push_back(trans); }
	inline void addRotationXKeyFrame(std::pair<float, float> rot) { rotationXKeyFrames.push_back(rot); }
	inline void addRotationYKeyFrame(std::pair<float, float> rot) { rotationYKeyFrames.push_back(rot); }
	inline void addRotationZKeyFrame(std::pair<float, float> rot) { rotationZKeyFrames.push_back(rot); }

	inline std::vector<std::pair<XMFLOAT4, float>> getTranslationKeyFrames() const { return translationKeyFrames; }
	inline std::vector<std::pair<float, float>> getRotationXKeyFrames() const { return rotationXKeyFrames; }
	inline std::vector<std::pair<float, float>> getRotationYKeyFrames() const { return rotationYKeyFrames; }
	inline std::vector<std::pair<float, float>> getRotationZKeyFrames() const { return rotationZKeyFrames; }

	inline size_t getNoOfTranslationKeyFrames() const { return translationKeyFrames.size(); }
	inline size_t getNoOfRotationXKeyFrames() const { return rotationXKeyFrames.size(); }
	inline size_t getNoOfRotationYKeyFrames() const { return rotationYKeyFrames.size(); }
	inline size_t getNoOfRotationZKeyFrames() const { return rotationZKeyFrames.size(); }

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

	//Animation Data
	std::vector<std::pair<XMFLOAT4, float>> translationKeyFrames;
	std::vector<std::pair<float, float>> rotationXKeyFrames;
	std::vector<std::pair<float, float>> rotationYKeyFrames;
	std::vector<std::pair<float, float>> rotationZKeyFrames;

	const std::string name; //Used for parsing
	const std::string parent;
};
#endif

