// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#include "TeddyModelClass.h"
#include "DDSTextureLoader.h"
#include "Facade.h"

TeddyModelClass::TeddyModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

TeddyModelClass::TeddyModelClass(const TeddyModelClass& other)
{}

TeddyModelClass::~TeddyModelClass()
{}

bool TeddyModelClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* context)
{
	bool result;
	result = InitializeBuffers(device, context);
	if (!result)
		return false;
	return true;
}

void TeddyModelClass::Shutdown()
{
	ShutdownBuffers();
}

void TeddyModelClass::Render(ID3D11DeviceContext* context)
{
	RenderBuffers(context);
}

int TeddyModelClass::GetIndexCount()
{
	return m_indexCount;
}

bool TeddyModelClass::InitializeBuffers(ID3D11Device* device, ID3D11DeviceContext* context)
{
	VertexType* vertices;
	unsigned int* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	ID3D11ShaderResourceView* m_shaderResourceView; // context->PSSetShaderResources(0,1,m_SRV);
	ID3D11SamplerState* m_samplerState;
	D3D11_SAMPLER_DESC ssDesc;

	HRESULT result;

	// import FBX data
	std::vector<VNUInfo> fbxVerts;

	EXP::Facade myF;
	fbxVerts = myF.getVertices(fbxVerts, "Teddy_Attack1.fbx");
	//getIndices?

	m_vertexCount = fbxVerts.size();
	m_indexCount = m_vertexCount;

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
		return false;
	indices = new unsigned int[m_indexCount];
	if (!indices)
		return false;

	// fill vert array
	VNUInfo* arr = &fbxVerts[0];
	for (int i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = XMFLOAT4(arr[i].vertInfo.x, arr[i].vertInfo.y, arr[i].vertInfo.z, 0.0f);
		vertices[i].color = XMFLOAT4(0, 0, 0, 0);
	}

	// fill index array

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
	indices = 0; vertices = 0;

	return true;
}

void TeddyModelClass::ShutdownBuffers()
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


void TeddyModelClass::RenderBuffers(ID3D11DeviceContext* context)
{
	unsigned stride[2];
	unsigned offset[2];
	ID3D11Buffer* bufferPointers[2];

	stride[0] = sizeof(VertexType);

	offset[0] = 0;


	bufferPointers[0] = m_vertexBuffer;

	context->IASetVertexBuffers(0, 1, bufferPointers, stride, offset);

	context->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->OMSetBlendState(0, 0, 0xffffffff);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}