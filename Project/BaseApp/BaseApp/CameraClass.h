#pragma once
// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_

#include "D3DClass.h"

class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix(XMMATRIX&);

	XMMATRIX ViewM();

private:
	float m_positionX, m_positionY, m_positionZ, m_rotationX, m_rotationY, m_rotationZ;
	XMMATRIX m_viewMatrix = XMMatrixInverse(0, XMMatrixTranslation(0, 1, -10));
	POINT point;
};










#endif
