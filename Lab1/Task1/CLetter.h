#include <windows.h>
#include <vector>

#include "CRectangle.h"

#pragma once
class CLetter
{
public:
	CLetter();
	CLetter(int x, int y, COLORREF color);
	void draw(HDC hdc);
	void move(int x, int y);
	void push(int x, int y, int w, int h);
	void jumping(double frequency);

private:
	int m_x;
	int m_y;
	double m_jumpPhase;
	double m_jumpDirection;
	double m_vy;
	std::vector<CRectangle> m_rectangles;
	COLORREF m_color;
};
