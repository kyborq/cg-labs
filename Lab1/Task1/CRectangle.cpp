#include "CRectangle.h"

CRectangle::CRectangle(int x, int y, int width, int height, COLORREF color)
	: m_x(x)
	, m_y(y)
	, m_width(width)
	, m_height(height)
	, m_color(color)
{
}

void CRectangle::draw(HDC hdc)
{
	RECT rect = { m_x, m_y, m_x + m_width, m_y + m_height };
	HBRUSH hBrush = CreateSolidBrush(m_color);
	FillRect(hdc, &rect, hBrush);
	DeleteObject(hBrush);
}

void CRectangle::move(int dx, int dy)
{
	m_x += dx;
	m_y += dy;
}

void CRectangle::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

int CRectangle::getY()
{
	return m_y;
}

void CRectangle::setY(int y)
{
	m_y = y;
}

int CRectangle::getHeight()
{
	return m_height;
}
