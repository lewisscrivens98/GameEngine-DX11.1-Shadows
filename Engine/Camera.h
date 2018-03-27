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

	void GetPosition(float&, float&, float&);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix(XMMATRIX&);

	void GenerateBaseViewMatrix();
	void GetBaseViewMatrix(XMMATRIX&);

	void RenderReflection(float);
	void GetReflectionViewMatrix(XMMATRIX&);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	XMMATRIX m_viewMatrix, m_baseViewMatrix, m_reflectionViewMatrix;
};

#endif