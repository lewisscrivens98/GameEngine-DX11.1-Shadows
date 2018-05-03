#ifndef _PLAYERCONTROLLER_H_
#define _PLAYERCONTROLLER_H_

///////////////////// CONTROLS ////////////////////////////
//
//	Movement:
//
//	W - Forward
//	A - Left
//  D - Right
//	S - Back
//	
//	SPACE - Up
//	LCONTROL - Down
//
//	LSHIFT - Speed Increase.
//
//	Scene Interaction:
//
//	M - Toggle Light Movement.
//	K - Toggle Smooth Shadows.
//	O - Show Shadow Map.
//	R - Rotate Cube.
//
//
/////////////////////////////////////////////////////////////

#include "Camera.h" 
#include "Input.h"
#include "Timer.h"
#include "Movement.h"

class PlayerController
{
public:
	PlayerController();
	PlayerController(const PlayerController&);
	~PlayerController();

	bool Initialize(HINSTANCE, HWND, int, int);
	bool Frame();
	bool HandleMovement(float);
	bool Render();

	void GetCameraViewMatrix(XMMATRIX&);
	void GetBaseCameraViewMatrix(XMMATRIX&);
	void GetPlayerPosition(XMFLOAT3&);

	void Shutdown();

private:

	Camera* m_camera;
	Input* m_input;
	Timer* m_timer;
	Movement* m_movement;

	bool currentInteraction;

public:
	 
	bool LightMovement;
	bool smoothShadows;
	bool showShadowmap;
	bool rotate;
};

#endif