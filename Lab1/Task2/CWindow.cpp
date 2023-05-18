#include "CWindow.h"

#include <windowsx.h>

CWindow::CWindow(HINSTANCE hInstance, LPCTSTR className, LPCTSTR title, int width, int height)
	: m_hInstance(hInstance)
	, m_hWnd(NULL)
{
	// Регистрация класса окна
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = CWindow::WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = className;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);

	m_hWnd = CreateWindow(
		className,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		this);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	// В идеале все данные стоит загружать файла
	SetBackground(RGB(212, 248, 255));

	CGroup roof(200, 200, RGB(100, 46, 72));
	roof.AddTriangle(0, 0, 100, 60);
	roof.AddRectangle(50, 0, 150, 60);

	CGroup wallFront(200, 200, RGB(191, 170, 131));
	wallFront.AddTriangle(150, 0, 100, 60);
	wallFront.AddRectangle(150, 60, 100, 100);

	CGroup wallSide(200, 200, RGB(206, 185, 146));
	wallSide.AddRectangle(0, 60, 150, 100);

	CGroup grass(0, 360, RGB(0, 255, 0));
	grass.AddRectangle(0, 0, 640, 100);

	CGroup houseWindows(200, 260);
	houseWindows.AddRectangle(20, 35, 30, 30);
	houseWindows.AddRectangle(95, 35, 30, 30);

	CGroup houseDoor(350, 260);
	houseDoor.AddRectangle(35, 35, 30, 70);

	CGroup houseChimney(325, 180);
	houseChimney.AddRectangle(0, 0, 20, 60);

	m_groups.push_back(roof);
	m_groups.push_back(wallSide);
	m_groups.push_back(wallFront);
	m_groups.push_back(houseWindows);
	m_groups.push_back(houseDoor);
	m_groups.push_back(houseChimney);
	
	CGroup fence(450, 280);
	for (int i = 0; i < 5; i++) 
	{
		fence.AddTriangle(i * 30 + 2, 0, 28, 30);
		fence.AddRectangle(i * 30 + 2, 30, 28, 70);
	}
	
	m_groups.push_back(fence);
	m_groups.push_back(grass);

	SetTimer(m_hWnd, 1, 50, NULL);
}

CWindow::~CWindow()
{
	if (m_hWnd)
	{
		DestroyWindow(m_hWnd);
	}
}

void CWindow::OnPaint(HDC hdc, PAINTSTRUCT ps)
{
	HBRUSH hBrush = CreateSolidBrush(m_background);
	FillRect(hdc, &ps.rcPaint, hBrush);

	// Отрисовка всех групп на экране
	for (CGroup group : m_groups)
	{
		group.Draw(hdc);
	}

	DeleteObject(hBrush);
}

void CWindow::OnDestroy()
{
	PostQuitMessage(0);
}

void CWindow::OnTimer(UINT_PTR nIDEvent)
{
	// Перерисовываем окно
	InvalidateRect(m_hWnd, NULL, TRUE);
}

void CWindow::SetBackground(COLORREF color)
{
	m_background = color;
}

HWND CWindow::GetHWND() const
{
	return m_hWnd;
}

LRESULT CWindow::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hWnd, &ps);
		OnPaint(hdc, ps);
		EndPaint(m_hWnd, &ps);
		break;
	}
	case WM_DESTROY: {
		OnDestroy();
		break;
	}
	case WM_TIMER: {
		OnTimer(wParam);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		// получить координаты клика мыши
		POINT clickPos = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

		// перетащить объект CGroup
		for (CGroup group : m_groups)
		{
			if (group.IsInside(clickPos))
			{
				group.DragAndDrop(clickPos, m_hWnd);
			}
		}
		//myGroup.DragAndDrop(clickPos, m_hWnd);
		break;
	}
	default:
		return DefWindowProc(m_hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CWindow::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CWindow* pWindow = NULL;
	if (message == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		pWindow = (CWindow*)pCreate->lpCreateParams;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWindow);
		pWindow->m_hWnd = hWnd;
	}
	else
	{
		pWindow = (CWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}

	if (pWindow)
	{
		return pWindow->HandleMessage(message, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
