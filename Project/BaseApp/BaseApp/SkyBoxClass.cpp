// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#include "SkyBoxClass.h"

SkyBoxClass::SkyBoxClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

SkyBoxClass::SkyBoxClass(const SkyBoxClass& other)
{}

SkyBoxClass::~SkyBoxClass()
{}

bool SkyBoxClass::Initialize(ID3D11Device* device)
{
	bool result;
	result = InitializeBuffers(device);
	if (!result)
		return false;
	return true;
}

void SkyBoxClass::Shutdown()
{
	ShutdownBuffers();
}

void SkyBoxClass::Render(ID3D11DeviceContext* context)
{
	RenderBuffers(context);
}

int SkyBoxClass::GetIndexCount()
{
	return m_indexCount;
}

bool SkyBoxClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 8;
	m_indexCount = 36;

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
		return false;
	indices = new unsigned long[m_indexCount];
	if (!indices)
		return false;

	vertices[0].position = XMFLOAT3(-2, 1, 2);
	vertices[1].position = XMFLOAT3(2, 1, 2);
	vertices[2].position = XMFLOAT3(-2, 1, -2);
	vertices[3].position = XMFLOAT3(2, 1, -2);
	vertices[4].position = XMFLOAT3(-2, 4, 2);
	vertices[5].position = XMFLOAT3(2, 4, 2);
	vertices[6].position = XMFLOAT3(-2, 4, -2);
	vertices[7].position = XMFLOAT3(2, 4, -2);

	vertices[0].color = XMFLOAT4(1, 0, 1, 1);
	vertices[1].color = XMFLOAT4(1, 0, 1, 1);
	vertices[2].color = XMFLOAT4(1, 0, 1, 1);
	vertices[3].color = XMFLOAT4(1, 0, 1, 1);
	vertices[4].color = XMFLOAT4(1, 0, 1, 1);
	vertices[5].color = XMFLOAT4(1, 0, 1, 1);
	vertices[6].color = XMFLOAT4(1, 0, 1, 1);
	vertices[7].color = XMFLOAT4(1, 0, 1, 1);

#pragma region Indicies
	//Bottom
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 1;
	indices[4] = 3;
	indices[5] = 2;

	//Top
	indices[6] = 5;
	indices[7] = 4;
	indices[8] = 7;
	indices[9] = 4;
	indices[10] = 6;
	indices[11] = 7;

	//Left
	indices[12] = 6;
	indices[13] = 4;
	indices[14] = 2;
	indices[15] = 4;
	indices[16] = 0;
	indices[17] = 2;

	//Right
	indices[18] = 5;
	indices[19] = 7;
	indices[20] = 1;
	indices[21] = 7;
	indices[22] = 3;
	indices[23] = 1;

	//Front
	indices[24] = 7;
	indices[25] = 6;
	indices[26] = 3;
	indices[27] = 6;
	indices[28] = 2;
	indices[29] = 3;

	//Back
	indices[30] = 4;
	indices[31] = 5;
	indices[32] = 0;
	indices[33] = 5;
	indices[34] = 1;
	indices[35] = 0;
#pragma endregion

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

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
		return false;

	delete[] vertices;
	delete[] indices;
	indices = 0; vertices = 0;

	return true;
}

void SkyBoxClass::ShutdownBuffers()
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


void SkyBoxClass::RenderBuffers(ID3D11DeviceContext* context)
{
	unsigned stride, offset;

	stride = sizeof(VertexType);
	offset = 0;

	context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}
