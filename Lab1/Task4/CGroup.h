#include <windows.h>
#include <vector>

#include "CFigure.h"

#pragma once
class CGroup
{
public:
	CGroup(int x, int y);
	CGroup(int x, int y, COLORREF color);

	void Draw(HDC hdc);
	void SetPosition(int x, int y);

	POINT GetPosition();

	void AddRectangle(int x, int y, int w, int h);
	void AddTriangle(int x, int y, int w, int h);
	void AddCircle(int x, int y, int radius);

	void DragAndDrop(POINT start, HWND hWnd);
	bool IsInside(POINT position);

private:
	int m_x;
	int m_y;

	std::vector<CFigure*> m_figures;
	COLORREF m_color;
};
