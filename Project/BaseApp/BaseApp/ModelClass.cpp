// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#include "ModelClass.h"
#include "DDSTextureLoader.h"

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_instanceBuffer = 0;
}

ModelClass::ModelClass(const ModelClass& other)
{}

ModelClass::~ModelClass()
{}

bool ModelClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* context)
{
	bool result;
	result = InitializeBuffers(device, context);
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

int ModelClass::GetInstanceCount()
{
	return m_instanceCount;
}

bool ModelClass::InitializeBuffers(ID3D11Device* device, ID3D11DeviceContext* context)
{
	VertexType* vertices;
	InstanceType* instances;
	unsigned int* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc, instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData, instanceData;
	ID3D11ShaderResourceView* m_shaderResourceView; // context->PSSetShaderResources(0,1,m_SRV);
	ID3D11SamplerState* m_samplerState;
	D3D11_SAMPLER_DESC ssDesc;

	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;
	m_instanceCount = 4;

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
		return false;
	indices = new unsigned int[m_indexCount];
	if (!indices)
		return false;
	instances = new InstanceType[m_instanceCount];
	if (!instances)
		return false;

	vertices[0].position = XMFLOAT3(-10, 0, 10);
	vertices[1].position = XMFLOAT3(10, 0, 10);
	vertices[2].position = XMFLOAT3(-10, 0, -10);
	vertices[3].position = XMFLOAT3(10, 0, -10);

	vertices[0].color = XMFLOAT4(0, 0, 0, 0);
	vertices[1].color = XMFLOAT4(1, 0, 0, 0);
	vertices[2].color = XMFLOAT4(0, 1, 0, 0);
	vertices[3].color = XMFLOAT4(1, 1, 0, 0);

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

	instances[0].position = XMFLOAT3(0, -10, 20);
	instances[1].position = XMFLOAT3(0, 0, 0);
	instances[2].position = XMFLOAT3(0, -5, 10);
	instances[3].position = XMFLOAT3(0, -15, 30);
	
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

	transparentBufferdesc.Usage = D3D11_USAGE_IMMUTABLE;
	transparentBufferdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	transparentBufferdesc.CPUAccessFlags = NULL;
	transparentBufferdesc.ByteWidth = m_indexCount * sizeof(unsigned int);
	transparentBufferdesc.MiscFlags = 0;
	transparentBufferdesc.StructureByteStride = 0;

	result = device->CreateBuffer(&transparentBufferdesc, &indexData, &transparentBuffer);
	if (FAILED(result))
		return false;

	instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	instanceBufferDesc.ByteWidth = sizeof(InstanceType)*m_instanceCount;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	instanceData.pSysMem = instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;
	
	result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &m_instanceBuffer);
	if (FAILED(result))
		return false;


	result = CreateDDSTextureFromFile(device, L"Assets\\texture.dds", nullptr, &m_shaderResourceView, 0);
	if (FAILED(result))
		return false;
	context->PSSetShaderResources(0, 1, &m_shaderResourceView);

	ZeroMemory(&ssDesc, sizeof(&ssDesc));
	ssDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	ssDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	ssDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	ssDesc.MipLODBias = 0;
	ssDesc.MaxAnisotropy = 1;
	ssDesc.ComparisonFunc = D3D11_COMPARISON_EQUAL;
	ssDesc.MinLOD = -(FLT_MAX);
	ssDesc.MaxLOD = (FLT_MAX);

	device->CreateSamplerState(&ssDesc, &m_samplerState);
	context->PSSetSamplers(0, 1, &m_samplerState);

	delete[] vertices;
	delete[] indices;
	delete[] instances;
	indices = 0; vertices = 0; instances = 0;

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
	if (m_instanceBuffer)
	{
		m_instanceBuffer->Release();
		m_instanceBuffer = 0;
	}
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* context)
{
	unsigned stride[2];
	unsigned offset[2];
	ID3D11Buffer* bufferPointers[2];

	stride[0] = sizeof(VertexType);
	stride[1] = sizeof(InstanceType);
	offset[0] = 0;
	offset[1] = 0;

	bufferPointers[0] = m_vertexBuffer;
	bufferPointers[1] = m_instanceBuffer;

	context->IASetVertexBuffers(0, 2, bufferPointers, stride, offset);

	if (GetAsyncKeyState('T'))
	{
		float blend[4] = { 0.5f, 0.5f, 0.5f, 1.0f };

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






















