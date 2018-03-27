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
	m_skybox = 0;
	m_playerController = 0;
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
	m_light->SetDirection(1.0f, 0.0f, 0.0f);// Direction vector for the light source.
	m_light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_light->SetSpecularPower(64.0f);

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

	// Create the Skybox object.
	m_skybox = new Model;
	if (!m_skybox)
	{
		return false;
	}

	// Initialize the Skybox object.
	result = m_skybox->Initialize(m_D3D->GetDevice(), "../Engine/data/Sphere.txt", L"../Engine/data/Skybox.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Skybox object.", L"Error", MB_OK);
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

	if (m_skybox)
	{
		m_skybox->Shutdown();
		delete m_skybox;
		m_skybox = 0;
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

	return;
}


bool Graphics::Frame()
{
	bool result;

	m_playerController->Frame();

	// Render the graphics.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool Graphics::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_playerController->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_playerController->GetCameraViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Setup the rotation and translation of the first model.
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(0));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(-10.0f, 0.0f, 0.0f));

	// Render the first model using the texture shader.
	m_cube->Render(m_D3D->GetDeviceContext());
	result = m_shaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_cube->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	m_cube->GetTexture());

	if (!result)
	{
		return false;
	}

	// Get player position for the skybox.
	float posX, posY, posZ;
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

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}


