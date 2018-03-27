////////////////////////////////////////////////////////////////////////////////
// Filename: Graphics.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "DirectX11.h"
#include "ShaderManager.h"
#include "Light.h"
#include "Model.h"
#include "BumpModel.h"
#include "PlayerController.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 3000.0f;
const float SCREEN_NEAR = 0.1f;


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

	bool Render();

private:

	DirectX11* m_D3D;
	ShaderManager* m_shaderManager;
	Light* m_light;
	Model* m_cube;
	Model* m_skybox;
	PlayerController* m_playerController;
};

#endif