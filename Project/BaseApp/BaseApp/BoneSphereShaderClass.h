#pragma once
// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#ifndef _BONESPHERESHADERCLASS_H_
#define _BONESPHERESHADERCLASS_H_

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <fstream>
#include "D3DClass.h"
using namespace DirectX;
using namespace std;

class BoneSphereShaderClass
{
private:

	struct MatrixBufferType
	{
		XMMATRIX world, view, projection;
	};

	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;

	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX);
	void RenderShader(ID3D11DeviceContext*, int, int);
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

public:
	BoneSphereShaderClass();
	BoneSphereShaderClass(const BoneSphereShaderClass&);
	~BoneSphereShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, int, XMMATRIX, XMMATRIX, XMMATRIX);

	D3DClass* d3d;
};


















#endif