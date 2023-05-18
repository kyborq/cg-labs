#include "CTriangle.h"

#include <vector>

CTriangle::CTriangle(int x, int y, int width, int height, COLORREF color) :
	m_x(x),
	m_y(y),
	m_width(width),
	m_height(height),
	m_color(color)
{
}

void CTriangle::Draw(HDC hdc)
{
	std::vector<POINT> points;
	points.push_back({ m_x + m_width / 2, m_y });
	points.push_back({ m_x, m_y + m_height });
	points.push_back({ m_x + m_width, m_y + m_height });

	HBRUSH hBrush = CreateSolidBrush(m_color);

	SelectObject(hdc, hBrush);
	Polygon(hdc, points.data(), points.size());

	DeleteObject(hBrush);
}

void CTriangle::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

const POINT CTriangle::GetPosition()
{
	return { m_x, m_y };
}

void CTriangle::SetSize(int width, int height)
{
	m_width = width;
	m_height = height;
}

bool CTriangle::IsInside(const POINT& point) const
{
	POINT v0 = { m_x + m_width / 2, m_y };
	POINT v1 = { m_x, m_y + m_height };
	POINT v2 = { m_x + m_width, m_y + m_height };

	POINT d0 = { v0.x - point.x, v0.y - point.y };
	POINT d1 = { v1.x - point.x, v1.y - point.y };
	POINT d2 = { v2.x - point.x, v2.y - point.y };


	double a = (double)abs((v1.x - v0.x) * (v2.y - v0.y) - (v2.x - v0.x) * (v1.y - v0.y)) / 2.0;
	double a0 = (double)abs((d1.x * d2.y - d2.x * d1.y)) / 2.0;
	double a1 = (double)abs((d0.x * d2.y - d2.x * d0.y)) / 2.0;
	double a2 = (double)abs((d0.x * d1.y - d1.x * d0.y)) / 2.0;

	return (a == a0 + a1 + a2);
}
