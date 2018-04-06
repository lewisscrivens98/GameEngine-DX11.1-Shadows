////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_


//////////////
// INCLUDES //
//////////////
#include <math.h>
#include <DirectXMath.h>

using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: Movement
////////////////////////////////////////////////////////////////////////////////
class Movement
{
public:
	Movement();
	Movement(const Movement&);
	~Movement();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);
	void SetMoveSpeed(bool, float moveSpeed);

	void GetPosition(XMFLOAT3&);
	void GetRotation(XMFLOAT3&);

	void SetFrameTime(float);

	void MoveForward(bool);
	void MoveBackward(bool);
	void MoveLeft(bool);
	void MoveRight(bool);
	void MoveUpward(bool);
	void MoveDownward(bool);
	void MoveMouse(int mouseChangeX, int mouseChangeY, float mouseSensitivity);


private:
	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;

	float m_frameTime;

	float m_forwardSpeed, m_backwardSpeed;
	float m_leftSpeed, m_rightSpeed;
	float m_upwardSpeed, m_downwardSpeed;
	float m_leftTurnSpeed, m_rightTurnSpeed;
	float m_lookUpSpeed, m_lookDownSpeed;

	float m_moveSpeed;
};

#endif