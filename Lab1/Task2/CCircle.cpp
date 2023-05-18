#include "CCircle.h"

CCircle::CCircle(int x, int y, int radius, COLORREF color) : 
	m_x(x), 
	m_y(y),
	m_radius(radius),
	m_color(color)
{
}

void CCircle::Draw(HDC hdc)
{
	HBRUSH brush = CreateSolidBrush(m_color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
	
	Ellipse(hdc, m_x - m_radius, m_y - m_radius, m_x + m_radius, m_y + m_radius);

	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}

void CCircle::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

const POINT CCircle::GetPosition()
{
	return { m_x, m_y };
}

void CCircle::SetSize(int radius)
{
	m_radius = radius;
}

bool CCircle::IsInside(const POINT& point) const
{
	int dx = point.x - m_x;
	int dy = point.y - m_y;
	int distanceSquared = dx * dx + dy * dy;
	int radiusSquared = m_radius * m_radius;

	return (distanceSquared <= radiusSquared);
}
