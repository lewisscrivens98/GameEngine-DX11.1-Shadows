/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 80.0f;
const float SCREEN_NEAR = 1.0f;
const int SHADOWMAP_WIDTH = 2048;
const int SHADOWMAP_HEIGHT = 2048;

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
	ID3D11ShaderResourceView* RenderBlurredShadows(ID3D11ShaderResourceView*, RenderTexture*);

	// 5 more passes to blur the shadow texture map before final render.
	bool RenderShadowTextures();
	bool RenderDownSampledTextures();
	bool RenderHorizontalBlurTextures();
	bool RenderVerticalBlurTextures();
	bool RenderUpSampledTextures();

private:

	DirectX11* m_D3D;
	ShaderManager* m_shaderManager;
	Light* m_light;
	Model* m_cube;
	Model* m_ground;
	PlayerController* m_playerController;
	RenderTexture *m_renderTexture, *m_shadowTexture, *m_downSampleTexture,
		*m_upSampleTexture, *m_horizontalBlurTexture, *m_verticalBlurTexture;
	RenderWindow *m_smallWindow, *m_fullWindow;
	
public:

	bool lightMovementSwitch;

};

#endif