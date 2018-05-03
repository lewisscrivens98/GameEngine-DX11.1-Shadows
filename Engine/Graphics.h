/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 1.0f;
const int SHADOWMAP_WIDTH = 1024;
const int SHADOWMAP_HEIGHT = 1024;

// Directional shadow map values.
const float SHADOWMAP_DEPTH = 50.0f;
const float SHADOWMAP_NEAR = 1.0f;


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
#include "RenderWindow.h"
#include "Skybox.h"


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
	bool LoadModels(HWND);
	void Shutdown();
	bool Frame(float);

private:

	bool HandleLightMovement(float);
	bool Render();
	bool RenderTextures();
	bool RenderBlurredShadows(ID3D11ShaderResourceView*, RenderTexture*);

	bool RenderPositionalShadowTextures();
	bool RenderDirectionlShadowDepthTextures();
	bool RenderDirectionlShadowTextures();

private:

	DirectX11* m_D3D;
	ShaderManager* m_shaderManager;
	Light* m_light;
	PlayerController* m_playerController;
	RenderTexture *m_renderDepth, *m_renderDirectionalDepth, *m_shadowTexture, *m_directionalShadowTexture, *m_downSampleTexture,
		*m_upSampleTexture, *m_horizontalBlurTexture, *m_verticalBlurTexture;
	RenderWindow *m_smallWindow, *m_fullWindow;

	//Models
	Model* m_cube;
	Model* m_ground;
	Model* m_skybox;

	float cubeRotation;
	
public:

	bool lightMovementSwitch;

};

#endif