// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#include "GraphicsClass.h"

GraphicsClass::GraphicsClass()
{
	m_Direct3D = 0;
	m_Camera = 0;

	///		Begin Ground Quad		///
	m_Model = 0;
	m_Shader = 0;
	///		End Ground Quad		///

	m_BoxModel = 0;
	m_BoxShader = 0;

	m_TeddyModel = 0;
	m_TeddyShader = 0;

	//m_SkyBox = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
		return false;

	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not init D3D", L"D3D Error", MB_OK);
		return false;
	}

	m_Camera = new CameraClass;
	if (!m_Camera)
		return false;
	m_Camera->SetPosition(0.0f, 1.0f, -10.0f);

	///		Begin Ground Quad		///

	m_Model = new ModelClass;
	if (!m_Model)
		return false;

	result = m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		MessageBox(hwnd, L"Could not Initialize model object", L"Model Error", MB_OK);
		return false;
	}

	m_Model->d3d = m_Direct3D;

	m_Shader = new ShaderClass;
	if (!m_Shader)
		return false;

	result = m_Shader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize shader object", L"Shader Error", MB_OK);
		return false;
	}
	m_Shader->d3d = m_Direct3D;

	///		End Ground Quad		///

	///		Begin Box		///
	m_BoxModel = new BoxModelClass;
	if (!m_BoxModel)
		return false;

	result = m_BoxModel->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		MessageBox(hwnd, L"Could not Initialize BoxModel object", L"BoxModel Error", MB_OK);
		return false;
	}

	m_BoxModel->d3d = m_Direct3D;

	m_BoxShader = new BoxShaderClass;
	if (!m_BoxShader)
		return false;

	result = m_BoxShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize BoxShader object", L"BoxShader Error", MB_OK);
		return false;
	}
	m_BoxShader->d3d = m_Direct3D;
	///		End Box		///

	///		Begin Teddy		///
	m_TeddyModel = new TeddyModelClass;
	if (!m_TeddyModel)
		return false;

	result = m_TeddyModel->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		MessageBox(hwnd, L"Could not Initialize TeddyModel object", L"TeddyModel Error", MB_OK);
		return false;
	}

	m_TeddyModel->d3d = m_Direct3D;

	m_TeddyShader = new TeddyShaderClass;
	if (!m_TeddyShader)
		return false;

	result = m_TeddyShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize TeddyShader object", L"TeddyShader Error", MB_OK);
		return false;
	}
	m_TeddyShader->d3d = m_Direct3D;
	///		End Teddy		///



	m_Light = new Light;
	if (!m_Light)
		return false;

	result = m_Light->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		MessageBox(hwnd, L"Could not Initialize light object", L"Light Error", MB_OK);
		return false;
	}


	//m_SkyBox = new SkyBoxClass;
	//if (!m_SkyBox)
	//	return false;

	//result = m_SkyBox->Initialize(m_Direct3D->GetDevice());
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not Initialize skybox object", L"Model Error", MB_OK);
	//	return false;
	//}
	return true;
}


void GraphicsClass::Shutdown()
{

	if (m_Shader)
	{
		m_Shader->Shutdown();
		delete m_Shader;
		m_Shader = 0;
	}

	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	//if (m_SkyBox)
	//{
	//	m_SkyBox->Shutdown();
	//	delete m_SkyBox;
	//	m_SkyBox = 0;
	//}

	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	result = Render();
	if (!result)
		return false;
	return true;
}


bool GraphicsClass::Render()
{
	XMMATRIX viewMatrix, projMatrix, worldMatrix;
	bool result;

	m_Direct3D->BeginScene(0.7f, 0.5f, 0.7f, 1.0f);

	m_Camera->Render();
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(projMatrix);

	///		Begin Ground Quad		///
	m_Model->Render(m_Direct3D->GetDeviceContext());
	result = m_Shader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), m_Model->GetInstanceCount(), worldMatrix, viewMatrix, projMatrix);
	if (!result)
		return false;
	///		End Ground Quad		///

	///		Begin Box Model		///
	m_BoxModel->Render(m_Direct3D->GetDeviceContext());
	result = m_BoxShader->Render(m_Direct3D->GetDeviceContext(), m_BoxModel->GetIndexCount(), NULL, worldMatrix, viewMatrix, projMatrix);
	if (!result)
		return false;
	///		End Box Model		///

	///		Begin Teddy Model		///
	m_TeddyModel->Render(m_Direct3D->GetDeviceContext());
	result = m_TeddyShader->Render(m_Direct3D->GetDeviceContext(), m_TeddyModel->GetIndexCount(), NULL, worldMatrix, viewMatrix, projMatrix);
	if (!result)
		return false;
	///		End Box Model		///

	m_Direct3D->EndScene();
	return true;
}