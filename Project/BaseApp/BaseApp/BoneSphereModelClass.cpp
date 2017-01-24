// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#include "BoneSphereModelClass.h"
#include "DDSTextureLoader.h"
#include "Facade.h"

BoneSphereModelClass::BoneSphereModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_instanceBuffer = 0;
}

BoneSphereModelClass::BoneSphereModelClass(const BoneSphereModelClass& other)
{}

BoneSphereModelClass::~BoneSphereModelClass()
{}

bool BoneSphereModelClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* context)
{
	bool result;
	result = InitializeBuffers(device, context);
	if (!result)
		return false;
	return true;
}

void BoneSphereModelClass::Shutdown()
{
	ShutdownBuffers();
}

void BoneSphereModelClass::Render(ID3D11DeviceContext* context)
{
	RenderBuffers(context);
}

int BoneSphereModelClass::GetIndexCount()
{
	return m_indexCount;
}

int BoneSphereModelClass::GetInstanceCount()
{
	return m_instanceCount;
}

bool BoneSphereModelClass::InitializeBuffers(ID3D11Device* device, ID3D11DeviceContext* context)
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

	// import FBX data
	std::vector<VNUInfo> fbxVerts;

	EXP::Facade myF;
	fbxVerts = myF.getVertices(fbxVerts, "Bone.fbx");
	//getIndices?

	m_vertexCount = fbxVerts.size();
	m_indexCount = m_vertexCount;

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
		return false;

	// TODO: set m_instanceCount to the number of bones in the model!
	m_instanceCount = 20;

	instances = new InstanceType[m_instanceCount];
	if (!instances)
		return false;

	// fill vert array
	VNUInfo* arr = &fbxVerts[0];
	for (int i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = XMFLOAT4(arr[i].vertInfo.x, arr[i].vertInfo.y, arr[i].vertInfo.z, 0.0f);
		vertices[i].color = XMFLOAT4(arr[i].textureInfo.x, arr[i].textureInfo.y, 0, 0);
	}

	// fill instance array


	for (int i = 0; i < m_instanceCount; i++)
	{
		instances[i].position = XMFLOAT3(i * 2, i*3, i*0.5f); // TODO: Pass in array of bone positions here!
	}

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
	delete[] instances;
	instances = 0; vertices = 0;

	return true;
}

void BoneSphereModelClass::ShutdownBuffers()
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


void BoneSphereModelClass::RenderBuffers(ID3D11DeviceContext* context)
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

	//context->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->OMSetBlendState(0, 0, 0xffffffff);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}