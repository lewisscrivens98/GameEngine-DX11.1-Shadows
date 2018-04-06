////////////////////////////////////////////////////////////////////////////////
// Filename: Camera.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_


//////////////
// INCLUDES //
//////////////

#include <DirectXMath.h> 
using namespace DirectX;


////////////////////////////////////////////////////////////////////////////////
// Class name: Camera
////////////////////////////////////////////////////////////////////////////////
class Camera
{
public:
	Camera();
	Camera(const Camera&);
	~Camera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	void GetPosition(XMFLOAT3&);
	void GetRotation(XMFLOAT3&);

	void Render();
	void GetViewMatrix(XMMATRIX&);

	void GenerateBaseViewMatrix();
	void GetBaseViewMatrix(XMMATRIX&);

	void RenderReflection(float);
	void GetReflectionViewMatrix(XMMATRIX&);

private:
	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;
	XMMATRIX m_viewMatrix, m_baseViewMatrix, m_reflectionViewMatrix;
};

#endif