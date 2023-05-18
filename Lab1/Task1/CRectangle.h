#include <windows.h>

#pragma once
class CRectangle
{
public:
	CRectangle(int x, int y, int width, int height, COLORREF color);

	void draw(HDC hdc);
	void move(int dx, int dy);
	void setPosition(int x, int y);
	int getY();
	void setY(int y);
	int getHeight();

private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	COLORREF m_color;
};
