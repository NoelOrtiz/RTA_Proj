// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#include "CameraClass.h"

CameraClass::CameraClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;
	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;	
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
	XMVECTOR up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	up.m128_f32[0] = 0.0f;
	up.m128_f32[1] = 1.0f;
	up.m128_f32[2] = 0.0f;

	position.m128_f32[0] = m_positionX;
	position.m128_f32[1] = m_positionY;
	position.m128_f32[2] = m_positionZ;
	
	lookAt.m128_f32[0] = 0.0f;
	lookAt.m128_f32[1] = 0.0f;
	lookAt.m128_f32[2] = 1.0f;

	pitch = m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;

	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	up = XMVector3TransformCoord(up, rotationMatrix);
	lookAt = position + lookAt;

	m_viewMatrix = XMMatrixLookAtLH(position, lookAt, up);
}

void CameraClass::GetViewMatrix(XMMATRIX& view)
{
	view = m_viewMatrix;
}