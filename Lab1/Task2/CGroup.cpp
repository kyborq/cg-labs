#include <chrono>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <string>

#include "CGroup.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCircle.h"

CGroup::CGroup(int x, int y) :
	m_x(x),
	m_y(y)
{
	m_color = RGB(0, 0, 0);
}

CGroup::CGroup(int x, int y, COLORREF color) : 
	m_x(x), 
	m_y(y), 
	m_color(color)
{
}

void CGroup::Draw(HDC hdc)
{
	for (auto& figure : m_figures)
	{
		figure->Draw(hdc);
	}
}

void CGroup::SetPosition(int x, int y)
{
	for (auto& figure : m_figures)
	{
		POINT point = figure->GetPosition();
		figure->SetPosition(x + point.x, y + point.y);
	}
}

POINT CGroup::GetPosition()
{
	return { m_x, m_y };
}

void CGroup::AddRectangle(int x, int y, int w, int h)
{
	CFigure* rectangle = new CRectangle(m_x + x, m_y + y, w, h, m_color);

	m_figures.push_back(rectangle);
}

void CGroup::AddTriangle(int x, int y, int w, int h)
{
	CFigure* triangle = new CTriangle(m_x + x, m_y + y, w, h, m_color);

	m_figures.push_back(triangle);
}

void CGroup::AddCircle(int x, int y, int radius)
{
	CFigure* circle = new CCircle(m_x + x, m_y + y, radius, m_color);

	m_figures.push_back(circle);
}

void CGroup::DragAndDrop(POINT start, HWND hWnd)
{
	SetCapture(hWnd); 

	POINT oldPos = GetPosition();
	POINT oldMousePos = start;

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
		{
			if (msg.wParam & MK_LBUTTON) 
			{
				POINT currentPoint = msg.pt;
				ScreenToClient(hWnd, &currentPoint);

				int dx = currentPoint.x - oldMousePos.x;
				int dy = currentPoint.y - oldMousePos.y;

				SetPosition(dx, dy);
				
				oldMousePos = msg.pt;

				InvalidateRect(hWnd, NULL, FALSE);
			}
			break;
		}
		case WM_LBUTTONUP:
		{
			ReleaseCapture(); 
			return;
		}
		}
	}
}

bool CGroup::IsInside(POINT position)
{
	return std::any_of(m_figures.begin(), m_figures.end(), [&](const auto& figure) 
		{
			return figure->IsInside(position);
		}
	);
}

