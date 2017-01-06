#pragma once

#include <Windows.h>
#include <DirectXMath.h>


class Light
{
public:
		DirectX::XMFLOAT3 direction;
		float pointRadius;
		DirectX::XMFLOAT4 dirColor;

		DirectX::XMFLOAT4 pointPosition;
		DirectX::XMFLOAT4 pointColor;

		DirectX::XMFLOAT4 spotColor;
		DirectX::XMFLOAT4 spotPosition;
		DirectX::XMFLOAT4 spotDirection;
		float spotRadius;

		DirectX::XMFLOAT3 padding;

		DirectX::XMFLOAT4 camPosition;

	Light();
	~Light();
};

