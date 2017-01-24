// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#include "BoneSphereShaderClass.h"
#include "Facade.h"


const DWORD modelNum = 5;

char files3[modelNum][256] =
{
	"Bone.fbx",
};
BoneSphereShaderClass::BoneSphereShaderClass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
}

BoneSphereShaderClass::BoneSphereShaderClass(const BoneSphereShaderClass&)
{}

BoneSphereShaderClass::~BoneSphereShaderClass()
{}

bool BoneSphereShaderClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	result = InitializeShader(device, hwnd, L"../BaseApp/BoneVS.fx", L"../BaseApp/BonePS.fx");
	if (!result)
		return false;
	return true;
}

void BoneSphereShaderClass::Shutdown()
{
	ShutdownShader();
}

bool BoneSphereShaderClass::Render(ID3D11DeviceContext* context, int indexCount, int instanceCount, XMMATRIX world, XMMATRIX view, XMMATRIX proj)
{
	bool result;

	result = SetShaderParameters(context, world, view, proj);
	if (!result)
		return false;

	RenderShader(context, indexCount, instanceCount);

	return true;
}

bool BoneSphereShaderClass::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{

	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;


	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	result = D3DCompileFromFile(vsFilename, NULL, NULL, "BoneVShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		else
			MessageBox(hwnd, vsFilename, L"Missing Vertex Shader File", MB_OK);
		return false;
	}

	result = D3DCompileFromFile(psFilename, NULL, NULL, "BonePShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		else
			MessageBox(hwnd, psFilename, L"Missing Pixel Shader File", MB_OK);
		return false;
	}

	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(result))
		return false;

	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(result))
		return false;

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "POSITION";
	polygonLayout[2].SemanticIndex = 1;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 1;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[2].InstanceDataStepRate = 1;

	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
		return false;

	vertexShaderBuffer->Release();
	pixelShaderBuffer->Release();
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result))
		return false;
	return true;

}

void BoneSphereShaderClass::ShutdownShader()
{
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}
	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}
	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}

}

// legacy function? DX10 protocols. here for inclusion's sake
void BoneSphereShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long long bufferSize, i;
	ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for (i = 0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}

bool BoneSphereShaderClass::SetShaderParameters(ID3D11DeviceContext* context, XMMATRIX world, XMMATRIX view, XMMATRIX proj)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;



	world = XMMatrixTranspose(world);
	view = XMMatrixTranspose(view);
	proj = XMMatrixTranspose(proj);

	result = context->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
		return false;

	dataPtr = (MatrixBufferType*)mappedResource.pData;

	dataPtr->projection = proj;
	dataPtr->view = view;
	dataPtr->world = world;

	context->Unmap(m_matrixBuffer, 0);

	bufferNumber = 0;

	context->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	return true;
}

void BoneSphereShaderClass::RenderShader(ID3D11DeviceContext* context, int indexCount, int instanceCount)
{
	context->IASetInputLayout(m_layout);
	context->VSSetShader(m_vertexShader, NULL, 0);
	context->PSSetShader(m_pixelShader, NULL, 0);
	context->DrawInstanced(indexCount, instanceCount, 0, 0);
	//context->Draw(indexCount, 0);
}