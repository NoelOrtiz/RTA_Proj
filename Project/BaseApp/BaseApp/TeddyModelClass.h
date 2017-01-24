#pragma once
// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#ifndef _TEDDYMODELCLASS_H_
#define _TEDDYMODELCLASS_H_

#include <vector>
#include "D3DClass.h"


class TeddyModelClass
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
	TeddyModelClass();
	TeddyModelClass(const TeddyModelClass&);
	~TeddyModelClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();


	D3DClass* d3d;
};










#endif