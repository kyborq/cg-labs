#include "CAWindow.h"

CAWindow::CAWindow(
	HINSTANCE hInstance, 
	LPCTSTR className, 
	LPCTSTR title, 
	int width, 
	int height
) 
	: m_hInstance(hInstance)
    , m_hWnd(NULL)
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = CAWindow::WindowProc;
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
		this
	);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	SetTimer(m_hWnd, 1, 50, NULL);
}

CAWindow::~CAWindow()
{
	if (m_hWnd)
	{
		DestroyWindow(m_hWnd);
	}
}

HWND CAWindow::GetHWND() const
{
	return m_hWnd;
}

HINSTANCE CAWindow::GetHInstance() const
{
	return HINSTANCE();
}

LPCTSTR CAWindow::GetClassNameW() const
{
	return LPCTSTR();
}

LPCTSTR CAWindow::GetTitle() const
{
	return ;
}

int CAWindow::GetWidth() const
{
	return 0;
}

int CAWindow::GetHeight() const
{
	return 0;
}

LRESULT CAWindow::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
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
	default:
		return DefWindowProc(m_hWnd, message, wParam, lParam);
	}
}

LRESULT CAWindow::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CAWindow* pWindow = NULL;
	if (message == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		pWindow = (CAWindow*)pCreate->lpCreateParams;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWindow);
		pWindow->m_hWnd = hWnd;
	}
	else
	{
		pWindow = (CAWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
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

void CAWindow::OnPaint(HDC hdc, PAINTSTRUCT ps)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
	FillRect(hdc, &ps.rcPaint, hBrush);

	// User defined function to draw object on screen in child class
	Start(hdc);

	DeleteObject(hBrush);
}

void CAWindow::OnDestroy()
{
	PostQuitMessage(0);
}

void CAWindow::OnTimer(UINT_PTR nIDEvent)
{
	// User defined function to update values in child class
	Update();
	InvalidateRect(m_hWnd, NULL, TRUE);
}
