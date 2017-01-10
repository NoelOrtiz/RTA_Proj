#pragma once
// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

#include "D3DClass.h"

class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
		XMFLOAT3 normal;
	};

	struct InstanceType
	{
		XMFLOAT3 position;
	};

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	ID3D11Buffer* m_vertexBuffer, *m_indexBuffer, *m_instanceBuffer;
	int m_vertexCount, m_indexCount, m_instanceCount;
	ID3D11Buffer *transparentBuffer;
	D3D11_BUFFER_DESC transparentBufferdesc;

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	int GetInstanceCount();

	bool transparent;

	D3DClass* d3d;

};










#endif