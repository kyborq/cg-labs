#include "CHangman.h"

CHangman::CHangman(CAWindow& window) 
	: CAWindow(window.GetHInstance(), window.GetClassName(), window.GetTitle(), window.GetWidth(), window.GetHeight())

{
	m_graphics = {};
	m_tries = 0;
}

void CHangman::Start(HDC hdc)
{
}

void CHangman::Update()
{
}
