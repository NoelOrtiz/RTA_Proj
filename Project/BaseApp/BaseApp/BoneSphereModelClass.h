#pragma once
// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#ifndef _BONESPHEREMODELCLASS_H_
#define _BONESPHEREMODELCLASS_H_

#include <vector>
#include "D3DClass.h"


class BoneSphereModelClass
{
private:
	struct VertexType
	{
		XMFLOAT4 position;
		XMFLOAT4 color;
	};

	struct InstanceType
	{
		XMFLOAT3 position;
	};

	bool InitializeBuffers(ID3D11Device*, ID3D11DeviceContext*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	ID3D11Buffer* m_vertexBuffer, *m_indexBuffer, *m_instanceBuffer;
	int m_vertexCount, m_indexCount, m_instanceCount;

public:
	BoneSphereModelClass();
	BoneSphereModelClass(const BoneSphereModelClass&);
	~BoneSphereModelClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	int GetInstanceCount();

	D3DClass* d3d;
};










#endif