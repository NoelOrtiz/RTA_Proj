// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#include "ModelClass.h"

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

ModelClass::ModelClass(const ModelClass& other)
{}

ModelClass::~ModelClass()
{}

bool ModelClass::Initialize(ID3D11Device* device)
{
	bool result;
	result = InitializeBuffers(device);
	if (!result)
		return false;
	return true;
}

void ModelClass::Shutdown()
{
	ShutdownBuffers();
}

void ModelClass::Render(ID3D11DeviceContext* context)
{
	RenderBuffers(context);
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned int* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
		return false;
	indices = new unsigned int[m_indexCount];
	if (!indices)
		return false;

	vertices[0].position = XMFLOAT3(-10, 0, 10);
	vertices[1].position = XMFLOAT3(10, 0, 10);
	vertices[2].position = XMFLOAT3(-10, 0, -10);
	vertices[3].position = XMFLOAT3(10, 0, -10);

	vertices[0].color = XMFLOAT4(1, 0, 0, 1);
	vertices[1].color = XMFLOAT4(0, 1, 0, 1);
	vertices[2].color = XMFLOAT4(0, 1, 1, 1);
	vertices[3].color = XMFLOAT4(0, 0, 0, 1);

	vertices[0].normal = XMFLOAT3(0, 1, 0);
	vertices[1].normal = XMFLOAT3(0, 1, 0);
	vertices[2].normal = XMFLOAT3(0, 1, 0);
	vertices[3].normal = XMFLOAT3(0, 1, 0);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 1;
	indices[4] = 3;
	indices[5] = 2;

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType)*m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
		return false;

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long)*m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	transparentBufferdesc.Usage = D3D11_USAGE_IMMUTABLE;
	transparentBufferdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	transparentBufferdesc.CPUAccessFlags = NULL;
	transparentBufferdesc.ByteWidth = m_indexCount * sizeof(unsigned int);
	transparentBufferdesc.MiscFlags = 0;
	transparentBufferdesc.StructureByteStride = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
		return false;

	result = device->CreateBuffer(&transparentBufferdesc, &indexData, &transparentBuffer);
	if (FAILED(result))
		return false;

	delete[] vertices;
	delete[] indices;
	indices = 0; vertices = 0;

	return true;	
}

void ModelClass::ShutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* context)
{
	unsigned stride, offset;

	stride = sizeof(VertexType);
	offset = 0;
	context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	if (GetAsyncKeyState('T'))
	{
		float blend[4] = { 0.75f, 0.75f, 0.75f, 1.0f };

		context->IASetIndexBuffer(transparentBuffer, DXGI_FORMAT_R32_UINT, 0);
		context->OMSetBlendState(d3d->transparency, blend, 0xffffffff);
		transparent = true;
	}
	else
	{
		context->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		context->OMSetBlendState(0, 0, 0xffffffff);

		transparent = false;
	}
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}






















