#include <chrono>
#include <cmath>
#include <math.h>
#include "CLetter.h"

CLetter::CLetter()
{
}

CLetter::CLetter(int x, int y, COLORREF color)
	: m_x(x)
	, m_y(y), m_color(color)
{
}

void CLetter::draw(HDC hdc)
{
	for (auto& rectangle : m_rectangles)
	{
		rectangle.draw(hdc);
	}
}

void CLetter::move(int x, int y)
{
	for (auto& rectangle : m_rectangles)
	{
		rectangle.move(x, y);
	}
}

void CLetter::push(int x, int y, int w, int h)
{
	m_rectangles.push_back(CRectangle(m_x + x, m_y + y, w, h, m_color));
}


void CLetter::jumping(double frequency)
{
	static double t = 0.0;
	const double dt = 0.02;
	const double amplitude = 20.0; // Амплитуда колебаний
	const double g = 9.81; // Ускорение свободного падения

	double y = m_y + amplitude * sin(2 * 3.14 * frequency * t) - g * t * t / 2.0;

	for (auto& r : m_rectangles)
	{
		// r.setY(y);
	}

	t += dt;
}
