// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#include "CameraClass.h"

CameraClass::CameraClass()
{
	//XMVECTOR up, position, lookAt;
	//float yaw, pitch, roll;
	//XMMATRIX rotationMatrix;
	//POINT newPosition;
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;
	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;	
	oldPosition.x = 0;
	oldPosition.y = 0;
	rotationMatrix = XMMatrixIdentity();
}

CameraClass::CameraClass(const CameraClass& other)
{}

CameraClass::~CameraClass()
{}

void CameraClass::SetPosition(float x, float y, float z)
{
	m_positionX = x; m_positionY = y; m_positionZ = z;
}

void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x; m_rotationY = y; m_rotationZ = z;
}

XMFLOAT3 CameraClass::GetPosition()
{
	return XMFLOAT3(m_positionX, m_positionY, m_positionZ);
}

XMFLOAT3 CameraClass::GetRotation()
{
	return XMFLOAT3(m_rotationX, m_rotationY, m_rotationZ);
}

void CameraClass::Render()
{

	GetCursorPos(&newPosition);

	up.m128_f32[0] = 0.0f;
	up.m128_f32[1] = 1.0f;
	up.m128_f32[2] = 0.0f;
	
	position.m128_f32[0] = m_positionX;
	position.m128_f32[1] = m_positionY;
	position.m128_f32[2] = m_positionZ;
	
	lookAt.m128_f32[0] = 0.0f;
	lookAt.m128_f32[1] = 0.0f;
	lookAt.m128_f32[2] = 1.0f;

	//pitch = m_rotationX * 0.0174532925f;
	//yaw = m_rotationY * 0.0174532925f;
	//roll = m_rotationZ * 0.0174532925f;

	if (GetAsyncKeyState('W'))
	{
		m_positionZ += 0.5f;
	}
	if (GetAsyncKeyState('A'))
	{
		m_positionX -= 0.5f;
	}
	if (GetAsyncKeyState('S'))
	{
		m_positionZ -= 0.5f;
	}
	if (GetAsyncKeyState('D'))
	{
		m_positionX += 0.5f;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		m_positionY += 0.5f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_positionY -= 0.5f;
	}
	
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		//GetCursorPos(&newPosition);
		//XMMATRIX tmp = m_viewMatrix;
		//
		//m_viewMatrix.r[3].m128_f32[0] = 0;
		//m_viewMatrix.r[3].m128_f32[1] = 0;
		//m_viewMatrix.r[3].m128_f32[2] = 0;
		
		pitch = ((newPosition.y - oldPosition.y)* 0.001f);
		yaw = ((newPosition.x - oldPosition.x)* 0.001f);
		
		//XMMATRIX XROT = XMMatrixRotationX((newPosition.y - oldPosition.y)  * 0.01f);
		//m_rotationX = (newPosition.y - oldPosition.y)  * 0.01f;
		//XMMATRIX YROT = XMMatrixRotationY((newPosition.x - oldPosition.x)  * 0.01f);
		//m_rotationY = (newPosition.x - oldPosition.x)  * 0.01f;
		//
		//
		//m_viewMatrix = XMMatrixMultiply(m_viewMatrix, YROT);
		//m_viewMatrix = XMMatrixMultiply(XROT, m_viewMatrix);
		//
		//m_viewMatrix.r[3].m128_f32[0] = tmp.r[3].m128_f32[0];
		//m_viewMatrix.r[3].m128_f32[1] = tmp.r[3].m128_f32[1];
		//m_viewMatrix.r[3].m128_f32[2] = tmp.r[3].m128_f32[2];
		//
		//rotationMatrix = XMMatrixMultiply(XROT, YROT);
		//rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
		oldPosition = newPosition;
		rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f);

	}

	
	
	lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	lookAt = XMVector3Normalize(lookAt);

	up = XMVector3TransformCoord(up, rotationMatrix);
	up = XMVector3Normalize(up);

	lookAt = position + lookAt;
	
	m_viewMatrix = XMMatrixLookAtLH(position, lookAt, up);
}

void CameraClass::GetViewMatrix(XMMATRIX& view)
{
	view = m_viewMatrix;
}