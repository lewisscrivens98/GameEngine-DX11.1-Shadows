////////////////////////////////////////////////////////////////////////////////
// Filename: Light.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Light.h"


Light::Light()
{
}


Light::Light(const Light& other)
{
}


Light::~Light()
{
}

// Set the ambient color of the light.
void Light::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

// Set the diffuse color of the light.
void Light::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

// Set the positioning of the light.
void Light::SetPosition(float x, float y, float z)
{
	m_position = XMFLOAT3(x, y, z);
	return;
}

// Set the look at directional vector.
void Light::SetLookAt(float x, float y, float z)
{
	m_lookAt.x = x;
	m_lookAt.y = y;
	m_lookAt.z = z;
	return;
}

// Return the lights ambient color.
XMFLOAT4 Light::GetAmbientColor()
{
	return m_ambientColor;
}

// Return the lights diffuse color.
XMFLOAT4 Light::GetDiffuseColor()
{
	return m_diffuseColor;
}

// Return the lights current position.
XMFLOAT3 Light::GetPosition()
{
	return m_position;
}

// Generate a view matrix for the light using the position and direction.
void Light::GenerateViewMatrix()
{
	XMVECTOR up, position, lookAt;

	// Create up vector.
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// Convert positional float 3 to a vector for the view matrix.
	position = XMVectorSet(m_position.x, m_position.y, m_position.z, 0.0f);

	// Convert m_lookat float 3 to a vector for the view matrix.
	lookAt = XMVectorSet(m_lookAt.x, m_lookAt.y, m_lookAt.z, 0.0f);

	// Create the view matrix from the three vectors.
	m_viewMatrix = XMMatrixLookAtLH(position, lookAt, up);

	return;
}

// Create a projection matrix to determin the area the lightsource will effect.
void Light::GenerateOrthoMatrix(float width, float screenDepth, float screenNear)
{
	// Create the projection matrix for the light.
	m_projectionMatrix = XMMatrixOrthographicLH(width, width, screenNear, screenDepth);

	return;
}

// Create a projection matrix to determin the area the lightsource will effect.
void Light::GenerateOrthoMatrix(float screenDepth, float screenNear)
{
	float fieldOfView = (float)XM_PI / 2.0f;
	float screenAspect = 1.0f;

	// Create the projection matrix for the light.
	m_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);

	return;
}

// Set given value to the light's view matrix
void Light::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}


void Light::GetProjectionMatrix(XMMATRIX& projectionMatrix)
{
	projectionMatrix = m_projectionMatrix;
	return;
}