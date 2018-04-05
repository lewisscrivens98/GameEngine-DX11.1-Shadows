////////////////////////////////////////////////////////////////////////////////
// Filename: Graphics.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Graphics.h"

Graphics::Graphics()
{
	m_D3D = 0;
	m_shaderManager = 0;
	m_light = 0;
	m_cube = 0;
	m_ground = 0;
	m_playerController = 0;
	m_renderTexture = 0;
	m_depthShader = 0;
}


Graphics::Graphics(const Graphics& other)
{
}


Graphics::~Graphics()
{
}


bool Graphics::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

	// Create the Direct3D object.
	m_D3D = new DirectX11;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_shaderManager = new ShaderManager;
	if (!m_shaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_shaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_light = new Light;
	if (!m_light)
	{
		return false;
	}

	// Initialize the light object.
	m_light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_light->SetPosition(0.0f, 8.0f, -5.0f);
	m_light->SetLookAt(0.0f, 0.0f, 0.0f);
	m_light->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);

	// Create the cube object.
	m_cube = new Model;
	if (!m_cube)
	{
		return false;
	}

	// Initialize the cube object.
	result = m_cube->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/marble.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the cube object.", L"Error", MB_OK);
		return false;
	}

	m_cube->SetPosition(0.0f, 0.0f, 0.0f);

	// Create the ground object.
	m_ground = new Model;
	if (!m_ground)
	{
		return false;
	}

	// Initialize the ground object.
	result = m_ground->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/metal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the ground object.", L"Error", MB_OK);
		return false;
	}

	m_ground->SetPosition(0.0f, -5.0f, 0.0f);

	// Create player controller.
	m_playerController = new PlayerController;
	if (!m_playerController)
	{
		return false;
	}
	
	// Initialise the player controller.
	result = m_playerController->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the player controller.", L"Error", MB_OK);
		return false;
	}

		// Create player controller.
	m_playerController = new PlayerController;
	if (!m_playerController)
	{
		return false;
	}
	
	// Initialise the player controller.
	result = m_playerController->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the player controller.", L"Error", MB_OK);
		return false;
	}

	// Create render texture class.
	m_renderTexture = new RenderTexture;
	if (!m_renderTexture)
	{
		return false;
	}

	// Initialise the render texture class.
	result = m_renderTexture->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the render texture class.", L"Error", MB_OK);
		return false;
	}

	// Create the depth shader object.
	m_depthShader = new DepthShader;
	if (!m_depthShader)
	{
		return false;
	}

	// Initialize the depth shader object.
	result = m_depthShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the depth shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void Graphics::Shutdown()
{
	// Release the model objects.
	if (m_cube)
	{
		m_cube->Shutdown();
		delete m_cube;
		m_cube = 0;
	}

	// Release the ground objects.
	if (m_ground)
	{
		m_ground->Shutdown();
		delete m_ground;
		m_ground = 0;
	}

	// Release the light object.
	if (m_light)
	{
		delete m_light;
		m_light = 0;
	}

	// Release the player controller.
	if (m_playerController)
	{
		m_playerController->Shutdown();
		delete m_playerController;
		m_playerController = 0;
	}

	// Release the shader manager object.
	if (m_shaderManager)
	{
		m_shaderManager->Shutdown();
		delete m_shaderManager;
		m_shaderManager = 0;
	}

	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the D3D object.
	if (m_renderTexture)
	{
		m_renderTexture->Shutdown();
		delete m_renderTexture;
		m_renderTexture = 0;
	}

	// Release the depth shader.
	if (m_depthShader)
	{
		m_depthShader->Shutdown();
		delete m_depthShader;
		m_depthShader = 0;
	}

	return;
}


bool Graphics::Frame()
{
	bool result;

	m_playerController->Frame();

	// Get player position to centre the skybox.
	float posX, posY, posZ;
	m_playerController->GetPlayerPosition(posX, posY, posZ);

	// Render the graphics.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool Graphics::RenderTextures()
{
	XMMATRIX worldMatrix, projectionMatrix, lightViewMatrix, lightProjectionMatrix, translateMatrix;
	float posX, posY, posZ;
	bool result;

	// Set the render target to be the render to texture.
	m_renderTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_renderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the light view matrix based on the light's position.
	m_light->GenerateViewMatrix();

	// Get the world matrix from the d3d object.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the view and orthographic matrices from the light object.
	m_light->GetViewMatrix(lightViewMatrix);
	m_light->GetProjectionMatrix(lightProjectionMatrix);

	// Setup the translation matrix for the cube model.
	m_cube->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(posX, posY, posZ));

	// Render the cube model with the depth shader.
	m_cube->Render(m_D3D->GetDeviceContext());
	result = m_depthShader->Render(m_D3D->GetDeviceContext(), m_cube->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if (!result)
	{
		return false;
	}

	// Setup the translation matrix for the cube model.
	m_ground->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(20.0f, 0.2f, 20.0f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(posX, posY, posZ));

	// Render the cube model with the depth shader.
	m_ground->Render(m_D3D->GetDeviceContext());
	result = m_depthShader->Render(m_D3D->GetDeviceContext(), m_ground->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}


bool Graphics::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix, lightViewMatrix, lightProjectionMatrix;
	float posX, posY, posZ;
	bool result;

	// First render the scenes textures.
	result = RenderTextures();
	if (!result)
	{
		return false;
	}

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_playerController->Render();

	// Generate the light view matrix based on the light's position.
	m_light->GenerateViewMatrix();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_playerController->GetCameraViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Get the view and orthographic matrices from the light object.
	m_light->GetViewMatrix(lightViewMatrix);
	m_light->GetProjectionMatrix(lightProjectionMatrix);

	// Setup the translation matrix for the cube model.
	m_cube->GetPosition(posX, posY, posZ);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(posX, posY, posZ));

	// Put the cube model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_cube->Render(m_D3D->GetDeviceContext());

	// Render the model using the shadow shader.
	result = m_shaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), m_cube->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, m_cube->GetTexture(), m_renderTexture->GetShaderResourceView(), m_light->GetPosition(),
		m_light->GetAmbientColor(), m_light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	// Setup the translation matrix for the ground model.
	m_ground->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(20.0f, 0.2f, 20.0f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(posX, posY, posZ));

	// Put the ground model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ground->Render(m_D3D->GetDeviceContext());

	// Render the model using the shadow shader.
	result = m_shaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), m_ground->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, m_ground->GetTexture(), m_renderTexture->GetShaderResourceView(), m_light->GetPosition(),
		m_light->GetAmbientColor(), m_light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}





/**			OLD SKYBOX
// Get player position for the skybox.
m_playerController->GetPlayerPosition(posX, posY, posZ);

// Setup the rotation and translation of the Skybox.
m_D3D->GetWorldMatrix(worldMatrix);
worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(-100.0f, -100.0f, -100.0f));// Revered the scale so that the sphere was turned inside out so the texture renders on the inside.
worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(posX, posY, posZ));// Sets the current skybox position to the player position so it stays at a constant distance from the player.

// Render the Skybox using the texture shader. Used the texture shader as the skybox isnt suposed to have shadows, reflections etc.
m_skybox->Render(m_D3D->GetDeviceContext());
m_shaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_skybox->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_skybox->GetTexture());

if (!result)
{
return false;
}
**/