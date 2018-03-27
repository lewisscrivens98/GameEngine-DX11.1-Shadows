#ifndef _PLAYERCONTROLLER_H_
#define _PLAYERCONTROLLER_H_

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
	void GetPlayerPosition(float&, float&, float&);

	void Shutdown();

private:

	Camera* m_camera;
	Input* m_input;
	Timer* m_timer;
	Movement* m_movement;

	float startX, startY, startZ, startRotX, startRotY, startRotZ;
};

#endif