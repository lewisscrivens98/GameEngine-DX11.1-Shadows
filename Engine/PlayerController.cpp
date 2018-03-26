#include "PlayerController.h"

using namespace std;

PlayerController::PlayerController()
{
	m_camera = 0;
	m_input = 0;
	m_timer = 0;
	m_movement = 0;

	// Starting rotation and positional values.
	startX = 0.0f;
	startY = 0.0f;
	startZ = -10.0f;
	startRotX = 0.0f;
	startRotY = 0.0f;
	startRotZ = 0.0f;
}

PlayerController::PlayerController(const PlayerController& other)
{

}

PlayerController::~PlayerController()
{

}

bool PlayerController::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

	// Create the camera object.
	m_camera = new CameraClass;
	if (!m_camera)
	{
		return false;
	}

	//m_camera->SetPosition(0.0f, 0.0f, -10.0f);

	m_input = new InputClass;
	if (!m_input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the player input object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_timer = new Timer;
	if (!m_timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create movement object.
	m_movement = new Movement;
	if (!m_movement)
	{
		return false;
	}

	// Set the initial position and rotation of the viewer.
	m_movement->SetPosition(startX, startY, startZ);
	m_movement->SetRotation(startRotX, startRotY, startRotZ);

	return true;
}

// Called every frame.
bool PlayerController::Frame()
{
	bool result;

	// Update the system stats.
	m_timer->Frame();

	// Read the user input.
	result = m_input->Frame();
	if (!result)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleMovement(m_timer->GetTime());
	if (!result)
	{
		return false;
	}

	// Render.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool PlayerController::HandleMovement(float frameTime)
{
	bool keyDown;
	float rotX, rotY, rotZ, posX, posY, posZ;// Positional and rotational values.
	int mouseChangeX, mouseChangeY;
	float movementSpeed = 1.0;// Used to affect movement speed easily.
	float mouseSensitivity = 0.1f;// Used to affect mouseMovement speed easily.

								  // Gets the mouseChange between frames for the X axis.
	mouseChangeX = m_input->GetMouseXChange();
	// Gets the mouseChange between frames for the Y axis.
	mouseChangeY = m_input->GetMouseYChange();

	// Set the frame time for calculating the updated position.
	m_movement->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_input->IsKeyDown(DIK_W);
	m_movement->MoveForward(keyDown);

	keyDown = m_input->IsKeyDown(DIK_S);
	m_movement->MoveBackward(keyDown);

	keyDown = m_input->IsKeyDown(DIK_A);
	m_movement->MoveLeft(keyDown);

	keyDown = m_input->IsKeyDown(DIK_D);
	m_movement->MoveRight(keyDown);

	keyDown = m_input->IsKeyDown(DIK_SPACE);
	m_movement->MoveUpward(keyDown);

	keyDown = m_input->IsKeyDown(DIK_LCONTROL);
	m_movement->MoveDownward(keyDown);

	keyDown = m_input->IsKeyDown(DIK_LSHIFT);
	m_movement->SetMoveSpeed(keyDown, movementSpeed);

	// Run the poisition method moveMouse and pass in variables from the input class.
	m_movement->MoveMouse(mouseChangeX, mouseChangeY, mouseSensitivity);

	// Get the new view point position/rotation.
	m_movement->GetPosition(posX, posY, posZ);
	m_movement->GetRotation(rotX, rotY, rotZ);

	// Reset the cursor to the centre of the screen as we now have mouse movement.
	m_input->ResetMousePosition();

	// Set the position of the camera.
	m_camera->SetPosition(posX, posY, posZ);
	m_camera->SetRotation(rotX, rotY, rotZ);

	return true;
}

bool PlayerController::Render()
{
	// Render the camera.
	m_camera->Render();

	return true;
}

void PlayerController::GetCameraViewMatrix(XMMATRIX& matrix)
{
	m_camera->GetViewMatrix(matrix);
	return;
}

void PlayerController::GetPlayerPosition(float& x, float& y, float& z)
{
	m_camera->GetPosition(x, y, z);

	return;
}

void PlayerController::Shutdown()
{
	// Release the camera object.
	if (m_camera)
	{
		delete m_camera;
		m_camera = 0;
	}

	// Release the input object.
	if (m_input)
	{
		m_input->Shutdown();
		delete m_input;
		m_input = 0;
	}

	// Release the timer object.
	if (m_timer)
	{
		delete m_timer;
		m_timer = 0;
	}

	// Release the movement object.
	if (m_movement)
	{
		delete m_movement;
		m_movement = 0;
	}
}

