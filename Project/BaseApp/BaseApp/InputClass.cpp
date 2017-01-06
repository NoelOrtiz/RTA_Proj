// Base Application Setup Instructions
// provided by rastertek.com (DX11 Series 2)

#include "InputClass.h"

InputClass::InputClass()
{}
InputClass::InputClass(const InputClass& other)
{}
InputClass::~InputClass()
{}

void InputClass::Initialize()
{
	for (int i = 0; i < 256; i++)
		m_keys[i] = false;
	return;
}

void InputClass::KeyDown(unsigned int in)
{
	m_keys[in] = true;
}
void InputClass::KeyUp(unsigned int in)
{
	m_keys[in] = false;
}
bool InputClass::IsKeyDown(unsigned int in)
{
	return m_keys[in];
}
