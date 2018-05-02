////////////////////////////////////////////////////////////////////////////////
// Filename: shadermanagerclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
	m_TextureShader = 0;
	m_LightShader = 0;
	m_BumpMapShader = 0;
	m_PositionalShadowShader = 0;
	m_DirectionalShadowShader = 0;
	m_SoftShadowShader = 0;
	m_DepthShader = 0;
}


ShaderManager::ShaderManager(const ShaderManager& other)
{
}


ShaderManager::~ShaderManager()
{
}


bool ShaderManager::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;


	// Create the texture shader object.
	m_TextureShader = new TextureShader;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShader;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the bump map shader object.
	m_BumpMapShader = new BumpmapShader;
	if(!m_BumpMapShader)
	{
		return false;
	}

	// Initialize the bump map shader object.
	result = m_BumpMapShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the bump map shader object.", L"Error", MB_OK);
		return false;
	}

	m_PositionalShadowShader = new PositionalShadowShader;
	if (!m_PositionalShadowShader)
	{
		return false;
	}

	// Initialize the positional Shadow shader object.
	result = m_PositionalShadowShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the positional shadow shader object.", L"Error", MB_OK);
		return false;
	}

	m_DirectionalShadowShader = new DirectionalShadowShader;
	if (!m_DirectionalShadowShader)
	{
		return false;
	}

	// Initialize the directional Shadow shader object.
	result = m_DirectionalShadowShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the directional shadow shader object.", L"Error", MB_OK);
		return false;
	}

	m_SoftShadowShader = new SoftShadowShader;
	if (!m_SoftShadowShader)
	{
		return false;
	}

	// Initialize the Soft Shadow shader object.
	result = m_SoftShadowShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the soft shadow shader object.", L"Error", MB_OK);
		return false;
	}

	m_DepthShader = new DepthShader;
	if (!m_DepthShader)
	{
		return false;
	}

	// Initialize the Shadow shader object.
	result = m_DepthShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the depth shader object.", L"Error", MB_OK);
		return false;
	}

	m_HorizontalBlurShader = new HorizontalBlurShader;
	if (!m_HorizontalBlurShader)
	{
		return false;
	}

	// Initialize the Horizontal blur shader object.
	result = m_HorizontalBlurShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the horizontal blur shader object.", L"Error", MB_OK);
		return false;
	}

	m_VerticalBlurShader = new VerticalBlurShader;
	if (!m_VerticalBlurShader)
	{
		return false;
	}

	// Initialize the Vertical blur shader object.
	result = m_VerticalBlurShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the vertical blur shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void ShaderManager::Shutdown()
{
	// Release the bump map shader object.
	if(m_BumpMapShader)
	{
		m_BumpMapShader->Shutdown();
		delete m_BumpMapShader;
		m_BumpMapShader = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the positional shadow shader object.
	if (m_PositionalShadowShader)
	{
		m_PositionalShadowShader->Shutdown();
		delete m_PositionalShadowShader;
		m_PositionalShadowShader = 0;
	}

	// Release the directional shadow shader object.
	if (m_DirectionalShadowShader)
	{
		m_DirectionalShadowShader->Shutdown();
		delete m_DirectionalShadowShader;
		m_DirectionalShadowShader = 0;
	}

	// Release the soft shadow shader object.
	if (m_SoftShadowShader)
	{
		m_SoftShadowShader->Shutdown();
		delete m_SoftShadowShader;
		m_SoftShadowShader = 0;
	}

	// Release the depth shader object.
	if (m_DepthShader)
	{
		m_DepthShader->Shutdown();
		delete m_DepthShader;
		m_DepthShader = 0;
	}

	// Release the horizontal blur shader object.
	if (m_HorizontalBlurShader)
	{
		m_HorizontalBlurShader->Shutdown();
		delete m_HorizontalBlurShader;
		m_HorizontalBlurShader = 0;
	}

	// Release the vertical blur shader object.
	if (m_VerticalBlurShader)
	{
		m_VerticalBlurShader->Shutdown();
		delete m_VerticalBlurShader;
		m_VerticalBlurShader = 0;
	}

	return;
}


bool ShaderManager::RenderTextureShader(ID3D11DeviceContext* device, int indexCount, const XMMATRIX &worldMatrix, const XMMATRIX &viewMatrix, const XMMATRIX &projectionMatrix,
											 ID3D11ShaderResourceView* texture)
{
	bool result;


	// Render the model using the texture shader.
	result = m_TextureShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if(!result)
	{
		return false;
	}

	return true;
}


bool ShaderManager::RenderLightShader(ID3D11DeviceContext* deviceContext, int indexCount, const XMMATRIX &worldMatrix, const XMMATRIX &viewMatrix, const XMMATRIX &projectionMatrix,
	ID3D11ShaderResourceView* texture, XMFLOAT3 lightDirection, XMFLOAT4 ambient, XMFLOAT4 diffuse,
	XMFLOAT3 cameraPosition, XMFLOAT4 specular, float specularPower)
{
	bool result;


	// Render the model using the light shader.
	result = m_LightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambient, diffuse, cameraPosition, 
								   specular, specularPower);
	if(!result)
	{
		return false;
	}

	return true;
}


bool ShaderManager::RenderBumpMapShader(ID3D11DeviceContext* deviceContext, int indexCount, const XMMATRIX &worldMatrix, const XMMATRIX &viewMatrix, const XMMATRIX &projectionMatrix,
	ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture, XMFLOAT3 lightDirection,
											 XMFLOAT4 diffuse)
{
	bool result;

	// Render the model using the bump map shader.
	result = m_BumpMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, lightDirection, diffuse);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderPositionalShadowShader(ID3D11DeviceContext* deviceContext, int indexCount, const XMMATRIX& worldMatrix,
		const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const XMMATRIX& lightViewMatrix, 
		const XMMATRIX& lightProjectionMatrix, ID3D11ShaderResourceView* depthMapTexture, 
XMFLOAT3 lightPosition)
{
	bool result;


	// Render the model using the shadow shader.
	result = m_PositionalShadowShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, depthMapTexture, lightPosition);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderDirectionalShadowShader(ID3D11DeviceContext* deviceContext, int indexCount, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix,
	const XMMATRIX& projectionMatrix, const XMMATRIX& lightViewMatrix, const XMMATRIX& lightProjectionMatrix,
	ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMapTexture, XMFLOAT3 lightDirection,
	XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor)
{
	bool result;

	// Render the model using the directional shadow shader.
	result = m_DirectionalShadowShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, lightProjectionMatrix, texture,
		depthMapTexture, lightDirection, ambientColor, diffuseColor);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderSoftShadowShader(ID3D11DeviceContext* deviceContext, int indexCount, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix,
	const XMMATRIX& projectionMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* shadowTexture,
	XMFLOAT3 lightPosition, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor)
{
	bool result;
	// Render the model using the soft shadow shader.
	result = m_SoftShadowShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, shadowTexture, lightPosition, ambientColor, diffuseColor);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderDepthShader(ID3D11DeviceContext* deviceContext, int indexCount, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix,
	const XMMATRIX& projectionMatrix)
{
	bool result;


	// Render the model using the depth shader.
	result = m_DepthShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderHorizontalBlurShader(ID3D11DeviceContext* deviceContext, int indexCount, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix,
	const XMMATRIX& projectionMatrix, ID3D11ShaderResourceView* texture, float screenWidth)
{
	bool result;


	// Render the model using the horizontal blur shader.
	result = m_HorizontalBlurShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, screenWidth);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderVerticalBlurShader(ID3D11DeviceContext* deviceContext, int indexCount, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix,
	const XMMATRIX& projectionMatrix, ID3D11ShaderResourceView* texture, float screenHeight)
{
	bool result;


	// Render the model using the vertical blur shader.
	result = m_VerticalBlurShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, screenHeight);
	if (!result)
	{
		return false;
	}

	return true;
}