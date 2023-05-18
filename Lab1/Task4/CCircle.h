#include <windows.h>
#include "CFigure.h"

#pragma once
class CCircle : public CFigure
{
public:
	CCircle(int x, int y, int radius, COLORREF color);

	void Draw(HDC hdc) override;
	void SetPosition(int x, int y) override;
	const POINT GetPosition() override;
	void SetSize(int radius) override;

	bool IsInside(const POINT& point) const override;

private:
	int m_x;
	int m_y;
	int m_radius;

	COLORREF m_color;
};
