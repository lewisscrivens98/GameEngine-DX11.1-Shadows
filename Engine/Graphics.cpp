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
	m_shadowTexture = 0;
	m_horizontalBlurTexture = 0;
	m_verticalBlurTexture = 0;
	m_downSampleTexture = 0;
	m_upSampleTexture = 0;
	m_smallWindow = 0;
	m_fullWindow = 0;
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
	int downSampleWidth, downSampleHeight;

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
	m_light->SetLookAt(0.0f, 0.0f, 0.0f);
	m_light->GenerateOrthoMatrix(SCREEN_DEPTH, SCREEN_NEAR);
	m_light->SetPosition(0.0f, 8.0f, -5.0f);
	lightMovementSwitch = true;

	// Create the cube object.
	m_cube = new Model;
	if (!m_cube)
	{
		return false;
	}

	// Initialize the cube object.
	result = m_cube->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/marble.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the cube object.", L"Error", MB_OK);
		return false;
	}

	m_cube->SetPosition(0.0f, 0.5f, 0.0f);

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

	m_ground->SetPosition(0.0f, -1.0f, 0.0f);

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

	// Create the shadow render to texture object.
	m_shadowTexture = new RenderTexture;
	if (!m_shadowTexture)
	{
		return false;
	}

	// Initialize the black and white render to texture object.
	result = m_shadowTexture->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shadow render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Set the size to sample down to.
	downSampleWidth = SHADOWMAP_WIDTH / 2;
	downSampleHeight = SHADOWMAP_HEIGHT / 2;

	// Create the down sample render to texture object.
	m_downSampleTexture = new RenderTexture;
	if (!m_downSampleTexture)
	{
		return false;
	}

	// Initialize the down sample render to texture object.
	result = m_downSampleTexture->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight, 100.0f, 1.0f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the down sample render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the small render window object.
	m_smallWindow = new RenderWindow;
	if (!m_smallWindow)
	{
		return false;
	}

	// Initialize the small render window object.
	result = m_smallWindow->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the small render window object.", L"Error", MB_OK);
		return false;
	}

	// Create the horizontal blur render to texture object.
	m_horizontalBlurTexture = new RenderTexture;
	if (!m_horizontalBlurTexture)
	{
		return false;
	}

	// Initialize the horizontal blur render to texture object.
	result = m_horizontalBlurTexture->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight, SCREEN_DEPTH, 0.1f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the horizontal blur render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the vertical blur render to texture object.
	m_verticalBlurTexture = new RenderTexture;
	if (!m_verticalBlurTexture)
	{
		return false;
	}

	// Initialize the vertical blur render to texture object.
	result = m_verticalBlurTexture->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight, SCREEN_DEPTH, 0.1f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the vertical blur render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the up sample render to texture object.
	m_upSampleTexture = new RenderTexture;
	if (!m_upSampleTexture)
	{
		return false;
	}

	// Initialize the up sample render to texture object.
	result = m_upSampleTexture->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, 0.1f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the up sample render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the full screen render window object.
	m_fullWindow = new RenderWindow;
	if (!m_fullWindow)
	{
		return false;
	}

	// Initialize the full screen render window object.
	result = m_fullWindow->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the full screen render window object.", L"Error", MB_OK);
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

	// Release the shadow texture object.
	if (m_shadowTexture)
	{
		m_shadowTexture->Shutdown();
		delete m_shadowTexture;
		m_shadowTexture = 0;
	}

	// Release the horizontal blur texture object.
	if (m_horizontalBlurTexture)
	{
		m_horizontalBlurTexture->Shutdown();
		delete m_horizontalBlurTexture;
		m_horizontalBlurTexture = 0;
	}

	// Release the vertical blur texture object.
	if (m_verticalBlurTexture)
	{
		m_verticalBlurTexture->Shutdown();
		delete m_verticalBlurTexture;
		m_verticalBlurTexture = 0;
	}

	// Release the down sample texture object.
	if (m_downSampleTexture)
	{
		m_downSampleTexture->Shutdown();
		delete m_downSampleTexture;
		m_downSampleTexture = 0;
	}

	// Release the up sample texture object.
	if (m_upSampleTexture)
	{
		m_upSampleTexture->Shutdown();
		delete m_upSampleTexture;
		m_upSampleTexture = 0;
	}

	// Release the small screen render window object.
	if (m_smallWindow)
	{
		m_smallWindow->Shutdown();
		delete m_smallWindow;
		m_smallWindow = 0;
	}

	// Release the full screen render window object.
	if (m_fullWindow)
	{
		m_fullWindow->Shutdown();
		delete m_fullWindow;
		m_fullWindow = 0;
	}

	return;
}


bool Graphics::Frame()
{
	bool result;

	m_playerController->Frame();

	// If the light movement is enabled then run the movement every frame.
	if (m_playerController->LightMovement)
	{
		result = HandleLightMovement();
		if (!result)
		{
			return false;
		}
	}

	// Render the graphics.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool Graphics::HandleLightMovement()
{
	XMFLOAT3 currentLightPos;

	// Move light left to right.
	currentLightPos = m_light->GetPosition();

	// Update the position of the light each frame.
	if (lightMovementSwitch)
	{
		currentLightPos.x += 0.02f;
	}
	else
	{
		currentLightPos.x -= 0.02f;
	}

	// Flip the lights movement.
	if (currentLightPos.x > 10.0f || currentLightPos.x < -10.0f)
	{
		lightMovementSwitch = !lightMovementSwitch;
	}

	// Update the position of the light.
	m_light->SetPosition(currentLightPos.x, currentLightPos.y, currentLightPos.z);

	return true;
}

bool Graphics::RenderTextures()
{
	XMMATRIX worldMatrix, lightViewMatrix, lightProjectionMatrix, translateMatrix;
	XMFLOAT3 pos;
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
	m_cube->GetPosition(pos);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.05f, 0.05f, 0.05f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(pos.x, pos.y, pos.z));

	// Render the cube model with the depth shader.
	m_cube->Render(m_D3D->GetDeviceContext());
	result = m_shaderManager->RenderDepthShader(m_D3D->GetDeviceContext(), m_cube->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Setup the translation matrix for the ground model.
	m_ground->GetPosition(pos);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(10.0f, 0.2f, 10.0f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(pos.x, pos.y, pos.z));

	// Render the ground model with the depth shader.
	m_ground->Render(m_D3D->GetDeviceContext());
	result = m_shaderManager->RenderDepthShader(m_D3D->GetDeviceContext(), m_ground->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
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


bool Graphics::RenderShadowTextures()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	XMMATRIX lightViewMatrix, lightProjectionMatrix;
	XMFLOAT3 pos;
	bool result;


	// Set the render target to be the render to texture.
	m_shadowTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_shadowTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_playerController->Render();

	// Generate the light view matrix based on the light's position.
	m_light->GenerateViewMatrix();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_playerController->GetCameraViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Get the light's view and projection matrices from the light object.
	m_light->GetViewMatrix(lightViewMatrix);
	m_light->GetProjectionMatrix(lightProjectionMatrix);

	// Setup the translation matrix for the cube model.
	m_cube->GetPosition(pos);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.05f, 0.05f, 0.05f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(pos.x, pos.y, pos.z));

	// Render the cube model using the shadow shader.
	m_cube->Render(m_D3D->GetDeviceContext());
	result = m_shaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), m_cube->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, m_renderTexture->GetShaderResourceView(), m_light->GetPosition());
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Setup the translation matrix for the ground model.
	m_ground->GetPosition(pos);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(10.0f, 0.2f, 10.0f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(pos.x, pos.y, pos.z));

	// Render the ground model using the shadow shader.
	m_ground->Render(m_D3D->GetDeviceContext());
	result = m_shaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), m_ground->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, m_renderTexture->GetShaderResourceView(), m_light->GetPosition());
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
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	XMFLOAT3 pos;
	bool result;

	// First render the scenes textures.
	result = RenderTextures();
	if (!result)
	{
		return false;
	}

	// Then render the scenes shadow map.
	result = RenderShadowTextures();
	if (!result)
	{
		return false;
	}

	ID3D11ShaderResourceView* blurredShadows = RenderBlurredShadows(m_shadowTexture->GetShaderResourceView(), m_upSampleTexture);

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_playerController->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_playerController->GetCameraViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Setup the translation matrix for the cube model.
	m_cube->GetPosition(pos);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.05f, 0.05f, 0.05f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(pos.x, pos.y, pos.z));

	// Put the cube model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_cube->Render(m_D3D->GetDeviceContext());

	// Render the model using the shadow shader.
	result = m_shaderManager->RenderSoftShadowShader(m_D3D->GetDeviceContext(), m_cube->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_cube->GetTexture(),
		blurredShadows, m_light->GetPosition(), m_light->GetAmbientColor(), m_light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	// Reset the world matrix for current model.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Setup the translation matrix for the ground model.
	m_ground->GetPosition(pos);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(10.0f, 0.2f, 10.0f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(pos.x, pos.y, pos.z));

	// Put the ground model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ground->Render(m_D3D->GetDeviceContext());

	// Render the model using the shadow shader.
	result = m_shaderManager->RenderSoftShadowShader(m_D3D->GetDeviceContext(), m_ground->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_ground->GetTexture(),
		blurredShadows, m_light->GetPosition(), m_light->GetAmbientColor(), m_light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

ID3D11ShaderResourceView* Graphics::RenderBlurredShadows(ID3D11ShaderResourceView* viewToBlur, RenderTexture* outputRenderTarget)
{
	XMMATRIX worldMatrix, baseViewMatrix, orthoMatrix;

	HRESULT result;
	m_playerController->Render();
	m_D3D->TurnZBufferOff();
	m_D3D->GetWorldMatrix(worldMatrix);
	m_playerController->GetBaseCameraViewMatrix(baseViewMatrix);

	// Tex 1
	m_downSampleTexture->SetRenderTarget(m_D3D->GetDeviceContext());
	m_downSampleTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f); // REALLY UNNECESSARY???
	m_downSampleTexture->GetOrthoMatrix(orthoMatrix);
	m_smallWindow->Render(m_D3D->GetDeviceContext());
	result = m_shaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_smallWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix, viewToBlur);

	// Tex 2
	m_horizontalBlurTexture->SetRenderTarget(m_D3D->GetDeviceContext());
	m_horizontalBlurTexture->GetOrthoMatrix(orthoMatrix);
	m_smallWindow->Render(m_D3D->GetDeviceContext());
	result = m_shaderManager->RenderHorizontalBlurShader(m_D3D->GetDeviceContext(), m_smallWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
		m_downSampleTexture->GetShaderResourceView(), (float)(SHADOWMAP_WIDTH * 0.5f));

	// Tex 3
	m_verticalBlurTexture->SetRenderTarget(m_D3D->GetDeviceContext());
	m_verticalBlurTexture->GetOrthoMatrix(orthoMatrix);
	m_smallWindow->Render(m_D3D->GetDeviceContext());
	result = m_shaderManager->RenderVerticalBlurShader(m_D3D->GetDeviceContext(), m_smallWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
		m_horizontalBlurTexture->GetShaderResourceView(), (float)(SHADOWMAP_HEIGHT * 0.5f));

	// Tex 4
	/*m_UpSampleTexure*/outputRenderTarget->SetRenderTarget(m_D3D->GetDeviceContext());
	/*m_UpSampleTexure*/outputRenderTarget->GetOrthoMatrix(orthoMatrix);
	m_fullWindow->Render(m_D3D->GetDeviceContext());
	result = m_shaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_fullWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
		m_verticalBlurTexture->GetShaderResourceView());

	m_D3D->TurnZBufferOn();
	m_D3D->SetBackBufferRenderTarget();
	m_D3D->ResetViewport();

	return outputRenderTarget->GetShaderResourceView();
	//return true;
}