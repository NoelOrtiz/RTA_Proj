#pragma once
// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#ifndef _D3DCLASS_H_
#define _D3DCLASS_H_

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

class D3DClass
{
public:
	D3DClass();
	D3DClass(const D3DClass&);
	~D3DClass();

	ID3D11BlendState* transparency;
	ID3D11RasterizerState* counterClockwise;
	ID3D11RasterizerState* clockwise;
	D3D11_BLEND_DESC blendDesc;
	D3D11_RENDER_TARGET_BLEND_DESC renderTargetblend;
	D3D11_RASTERIZER_DESC rasterDesc;

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(XMMATRIX&);
	void GetWorldMatrix(XMMATRIX&);
	void GetOrthoMatrix(XMMATRIX&);

	void GetVideoCardInfo(char*, int&);

	D3DClass* GetD3DInstance();

private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	XMMATRIX m_projectionMatrix, m_worldMatrix, m_orthoMatrix;

	

};


#endif