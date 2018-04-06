/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 100.0f;
const float SCREEN_NEAR = 1.0f;
const int SHADOWMAP_WIDTH = 1024;
const int SHADOWMAP_HEIGHT = 1024;

////////////////////////////////////////////////////////////////////////////////
// Filename: Graphics.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "DirectX11.h"
#include "ShaderManager.h"
#include "Light.h"
#include "Model.h"
#include "BumpModel.h"
#include "PlayerController.h"
#include "RenderTexture.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: Graphics
////////////////////////////////////////////////////////////////////////////////
class Graphics
{
public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

private:

	bool HandleLightMovement();
	bool Render();
	bool RenderTextures();

private:

	DirectX11* m_D3D;
	ShaderManager* m_shaderManager;
	Light* m_light;
	Model* m_cube;
	Model* m_ground;
	PlayerController* m_playerController;
	RenderTexture* m_renderTexture;
	DepthShader* m_depthShader;
	
public:

	bool lightMovementSwitch;

};

#endif