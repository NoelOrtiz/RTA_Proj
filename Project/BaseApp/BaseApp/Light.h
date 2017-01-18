#pragma once

#include <Windows.h>
#include <DirectXMath.h>
#include "D3DClass.h"

using namespace DirectX;

class Light
{
public:
	struct Lights {

		XMFLOAT3 direction;
		float pointRadius;
		XMFLOAT4 dirColor;

		XMFLOAT4 pointPosition;
		XMFLOAT4 pointColor;

		XMFLOAT4 spotColor;
		XMFLOAT4 spotPosition;
		XMFLOAT4 spotDirection;
		float spotRadius;

		XMFLOAT3 padding;
	};



	ID3D11Buffer *lightBuffer;

	bool Initialize(ID3D11Device*, ID3D11DeviceContext* context);
	bool InitializeBuffers(ID3D11Device*, ID3D11DeviceContext* context);
	bool SetLightParameters(ID3D11DeviceContext*, Lights light);

	void ShutdownBuffers();

	Light();
	~Light();
};

