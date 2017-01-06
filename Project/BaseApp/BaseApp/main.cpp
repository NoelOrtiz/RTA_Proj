// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#include "SystemClass.h"
#include "Light.h"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System;
	bool result;

	//Default light variable
	Light light;

	// Create the system and make sure it exists
	System = new SystemClass;
	if (!System)
		return 0;

	// Initialize the system and start the loop if it works
	result = System->Initialize();
	if (result)
		System->Run();


	// Once we're done, shut down and clean up.
	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}