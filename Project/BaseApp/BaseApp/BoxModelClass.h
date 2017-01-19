#pragma once
// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#ifndef _BOXMODELCLASS_H_
#define _BOXMODELCLASS_H_

#include <vector>
#include "D3DClass.h"


class BoxModelClass
{
private:
	struct VertexType
	{
		XMFLOAT4 position;
		XMFLOAT4 color;
	};

	bool InitializeBuffers(ID3D11Device*, ID3D11DeviceContext*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	ID3D11Buffer* m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

public:
	BoxModelClass();
	BoxModelClass(const BoxModelClass&);
	~BoxModelClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	bool transparent;

	D3DClass* d3d;
};










#endif