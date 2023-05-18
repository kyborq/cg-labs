#include "CRectangle.h"

CRectangle::CRectangle(int x, int y, int width, int height, COLORREF color) :
	m_x(x),
	m_y(y),
	m_width(width),
	m_height(height),
	m_color(color)
{
}

void CRectangle::Draw(HDC hdc)
{
	HBRUSH brush = CreateSolidBrush(m_color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
	
	RECT rect = { m_x, m_y, m_x + m_width, m_y + m_height };
	FillRect(hdc, &rect, brush);
	
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}

void CRectangle::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

const POINT CRectangle::GetPosition()
{
	return { m_x, m_y };
}

void CRectangle::SetSize(int width, int height)
{
	m_width = width;
	m_height = height;
}

bool CRectangle::IsInside(const POINT& point) const
{
	return (point.x >= m_x && point.x <= m_x + m_width && point.y >= m_y && point.y <= m_y + m_height);
}
