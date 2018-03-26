////////////////////////////////////////////////////////////////////////////////
// Filename: Movement.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Movement.h"


Movement::Movement()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_frameTime = 0.0f;

	m_forwardSpeed = 0.0f;
	m_backwardSpeed = 0.0f;
	m_leftSpeed = 0.0f;
	m_rightSpeed = 0.0f;
	m_upwardSpeed = 0.0f;
	m_downwardSpeed = 0.0f;
	m_leftTurnSpeed = 0.0f;
	m_rightTurnSpeed = 0.0f;
	m_lookUpSpeed = 0.0f;
	m_lookDownSpeed = 0.0f;

	m_moveSpeed = 0.5f;
}


Movement::Movement(const Movement& other)
{
}


Movement::~Movement()
{
}


void Movement::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void Movement::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}

void Movement::SetMoveSpeed(bool keydown, float moveSpeed) //Used to set the movement speed of the camera which effects all movement variables.
{
	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_moveSpeed = moveSpeed;
	}
	else
	{
		m_moveSpeed = 0.5f;
	}


	return;
}


void Movement::GetPosition(float& x, float& y, float& z)
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;
	return;
}


void Movement::GetRotation(float& x, float& y, float& z)
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;
	return;
}


void Movement::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}


void Movement::MoveForward(bool keydown)
{
	float radians;


	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_forwardSpeed += m_frameTime * 0.001f;

		if (m_forwardSpeed > (m_frameTime * 0.03f))
		{
			m_forwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_forwardSpeed -= m_frameTime * 0.0007f;

		if (m_forwardSpeed < 0.0f)
		{
			m_forwardSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	radians = m_rotationY * 0.0174532925f;

	// Update the position.
	m_positionX += sinf(radians) * (m_forwardSpeed * m_moveSpeed);
	m_positionZ += cosf(radians) * (m_forwardSpeed * m_moveSpeed);

	return;
}


void Movement::MoveBackward(bool keydown)
{
	float radians;


	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_backwardSpeed += m_frameTime * 0.001f;

		if (m_backwardSpeed > (m_frameTime * 0.03f))
		{
			m_backwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_backwardSpeed -= m_frameTime * 0.0007f;

		if (m_backwardSpeed < 0.0f)
		{
			m_backwardSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	radians = m_rotationY * 0.0174532925f;

	// Update the position.
	m_positionX -= sinf(radians) * (m_backwardSpeed * m_moveSpeed);
	m_positionZ -= cosf(radians) * (m_backwardSpeed * m_moveSpeed);

	return;
}

void Movement::MoveLeft(bool keydown)
{
	float radians;

	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_leftSpeed += m_frameTime * 0.001f;

		if (m_leftSpeed > (m_frameTime * 0.03f))
		{
			m_leftSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_leftSpeed -= m_frameTime * 0.0007f;

		if (m_leftSpeed < 0.0f)
		{
			m_leftSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	radians = (m_rotationY - 90) * 0.0174532925f; //Rotates movement 90 degrees so its left and right instead of forward and backward.

												  // Update the position.
	m_positionX += sinf(radians) * (m_leftSpeed * m_moveSpeed);
	m_positionZ += cosf(radians) * (m_leftSpeed * m_moveSpeed);


	return;
}

void Movement::MoveRight(bool keydown)
{
	float radians;

	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_rightSpeed += m_frameTime * 0.001f;

		if (m_rightSpeed > (m_frameTime * 0.03f))
		{
			m_rightSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_rightSpeed -= m_frameTime * 0.0007f;

		if (m_rightSpeed < 0.0f)
		{
			m_rightSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	radians = (m_rotationY - 90) * 0.0174532925f; //Rotates movement 90 degrees so its left and right instead of forward and backward.

												  // Update the position.
	m_positionX -= sinf(radians) * (m_rightSpeed * m_moveSpeed);
	m_positionZ -= cosf(radians) * (m_rightSpeed * m_moveSpeed);

	return;
}

void Movement::MoveUpward(bool keydown)
{
	// Update the upward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_upwardSpeed += m_frameTime * 0.003f;

		if (m_upwardSpeed > (m_frameTime * 0.03f))
		{
			m_upwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_upwardSpeed -= m_frameTime * 0.002f;

		if (m_upwardSpeed < 0.0f)
		{
			m_upwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY += (m_upwardSpeed * m_moveSpeed);

	return;
}


void Movement::MoveDownward(bool keydown)
{
	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_downwardSpeed += m_frameTime * 0.003f;

		if (m_downwardSpeed > (m_frameTime * 0.03f))
		{
			m_downwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_downwardSpeed -= m_frameTime * 0.002f;

		if (m_downwardSpeed < 0.0f)
		{
			m_downwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY -= (m_downwardSpeed * m_moveSpeed);

	return;
}

void Movement::MoveMouse(int mouseChangeX, int mouseChangeY, float mouseSensitivity)//When the method is ran these variables must be passed to the method.
{
	if ((m_rotationX + (mouseChangeY * mouseSensitivity)) <= 90 || (m_rotationX + (mouseChangeY * mouseSensitivity)) >= -90)//Check that any added rotation doesnt exceed the boundries for X rotation.
	{
		m_rotationX += mouseChangeY * mouseSensitivity;//Set rotationX to rotationX + mouse change on the y axis, the smaller the mouse sensitivity the more it reduces the rotation.
	}

	m_rotationY += mouseChangeX * mouseSensitivity;//Set rotationX to rotationX + mouse change on the y axis.
}