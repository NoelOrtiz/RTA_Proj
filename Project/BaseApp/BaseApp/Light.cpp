#include "Light.h"



Light::Light()
{
}


Light::~Light()
{
}

bool Light::Initialize(ID3D11Device* device)
{
	bool result;
	result = InitializeBuffers(device);
	if (!result)
		return false;
	return true;
}

bool Light::InitializeBuffers(ID3D11Device* device)
{
	Lights light;

	D3D11_BUFFER_DESC lightBufferdesc;

	D3D11_SUBRESOURCE_DATA lightData;

	light.dirColor = { 1,1,1,1 };
	light.direction = { -1.0f, -0.75f, 0.0f };

	light.pointPosition = { 0, 3, 0, 1 };
	light.pointColor = { 0.0f, 1.0f, 1.0f, 1.0f };
	light.pointRadius = 10.0f;

	light.spotColor = { 1.0f, 1.0f, 0.0f, 1.0f };
	light.spotDirection = { 0, 0, 1, 1 };
	light.spotPosition = { -5, 0, -10, 1 };
	light.spotRadius = 0.93f;

	lightBufferdesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferdesc.ByteWidth = sizeof(Lights);

	lightData.pSysMem = &light;
	device->CreateBuffer(&lightBufferdesc, &lightData, &lightBuffer);

	return true;
}

bool Light::SetLightParameters(ID3D11DeviceContext* context, Lights light)
{
	D3D11_MAPPED_SUBRESOURCE lightMap;

	Lights* lights;

	context->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, NULL, &lightMap);

	lights = (Lights*)lightMap.pData;

	lights->direction = light.direction;
	lights->pointRadius = light.pointRadius;
	lights->dirColor = light.dirColor;
	lights->pointPosition = light.pointPosition;
	lights->pointColor = light.pointColor;
	lights->spotColor = light.spotColor;
	lights->spotPosition = light.spotPosition;
	lights->spotDirection = light.spotDirection;
	lights->spotRadius = light.spotRadius;
	lights->padding = light.padding;

	context->Unmap(lightBuffer, 0);

	context->PSSetConstantBuffers(0, 1, &lightBuffer);

	return true;
}

void Light::ShutdownBuffers()
{
	if (lightBuffer)
	{
		lightBuffer->Release();
		lightBuffer = 0;
	}
}