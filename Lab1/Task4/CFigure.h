#pragma once
#include <windows.h>

class CFigure
{
public:
	virtual ~CFigure() = default;

	virtual void Draw(HDC hdc) = 0;
	virtual void SetPosition(int x, int y) = 0;
	virtual const POINT GetPosition() = 0;
	virtual void SetSize(int width, int height) {};
	virtual void SetSize(int size) {};
	virtual bool IsInside(const POINT& point) const = 0;
};

