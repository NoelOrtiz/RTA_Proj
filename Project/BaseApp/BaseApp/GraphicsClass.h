#pragma once
// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include "D3DClass.h"
#include "CameraClass.h"
#include "ModelClass.h"
#include "ShaderClass.h"

#include "BoxModelClass.h"
#include "BoxShaderClass.h"

#include "TeddyModelClass.h"
#include "TeddyShaderClass.h"

#include "MageModelClass.h"
#include "MageShaderClass.h"

#include "BoneSphereModelClass.h"
#include "BoneSphereShaderClass.h"

#include "SkyBoxClass.h"
#include "Light.h"


const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;			//Farplane
const float SCREEN_NEAR = 0.1f;				//Nearplane

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	
	// Ground Quad
	ModelClass* m_Model;
	ShaderClass* m_Shader;

	// Box Model
	BoxModelClass* m_BoxModel;
	BoxShaderClass* m_BoxShader;

	// Teddy Model
	TeddyModelClass* m_TeddyModel;
	TeddyShaderClass* m_TeddyShader;

	// Mage Model
	MageModelClass* m_MageModel;
	MageShaderClass* m_MageShader;
	
	// BoneSphere Model
	BoneSphereModelClass* m_BoneSphereModel;
	BoneSphereShaderClass* m_BoneSphereShader;


	Light* m_Light;
	
	
	//SkyBoxClass* m_SkyBox;
};


#endif