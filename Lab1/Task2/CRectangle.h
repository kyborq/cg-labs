#include <windows.h>
#include "CFigure.h"

#pragma once
class CRectangle : public CFigure
{
public:
	CRectangle(int x, int y, int width, int height, COLORREF color);

	void Draw(HDC hdc) override;
	void SetPosition(int x, int y) override;
	const POINT GetPosition() override;
	void SetSize(int width, int height) override;

	bool IsInside(const POINT& point) const override;

private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;

	COLORREF m_color;
};
