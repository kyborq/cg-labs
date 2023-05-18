#include "CWindow.h"

CWindow::CWindow(HINSTANCE hInstance, LPCTSTR className, LPCTSTR title, int width, int height)
	: m_hInstance(hInstance)
	, m_hWnd(NULL)
{
	// Регистрация класса окна
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = CWindow::windowProc;
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

	// Формирование буквы П
	CLetter letterP(50, 50, RGB(0, 255, 0));
	letterP.push(0, 0, 10, 80);
	letterP.push(0, 0, 50, 10);
	letterP.push(50, 0, 10, 80);
	
	// Формирование буквы К
	CLetter letterK(120, 50, RGB(0, 255, 255));
	letterK.push(0, 0, 10, 80);
	letterK.push(10, 35, 30, 10);
	letterK.push(40, 0, 10, 35);
	letterK.push(40, 45, 10, 35);

	// Формирование буквы Э
	CLetter letterE(180, 50, RGB(255, 50, 30));
	letterE.push(40, 10, 10, 60);
	letterE.push(0, 0, 40, 10);
	letterE.push(0, 70, 40, 10);
	letterE.push(20, 35, 30, 10);

	// Добавление букв
	m_letters.push_back(letterP);
	m_letters.push_back(letterK);
	m_letters.push_back(letterE);

	SetTimer(m_hWnd, 1, 50, NULL);
}

CWindow::~CWindow()
{
	if (m_hWnd)
	{
		DestroyWindow(m_hWnd);
	}
}

void CWindow::onPaint(HDC hdc, PAINTSTRUCT ps)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
	FillRect(hdc, &ps.rcPaint, hBrush);

	// Отрисовка всех букв на экране
	for (CLetter letter : m_letters)
	{
		letter.draw(hdc);
	}

	DeleteObject(hBrush);
}

void CWindow::onDestroy()
{
	PostQuitMessage(0);
}

void CWindow::onTimer(UINT_PTR nIDEvent)
{
	// TODO: Прыжки для букв работают, но требуется доработка

	// m_letters[0].jumping(2.3);
	// m_letters[1].jumping(2.1);
	// m_letters[2].jumping(2.2);

	
	// Перерисовываем окно
	InvalidateRect(m_hWnd, NULL, TRUE);
}

HWND CWindow::hWnd() const
{
	return m_hWnd;
}

LRESULT CWindow::handleMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hWnd, &ps);
		onPaint(hdc, ps);
		EndPaint(m_hWnd, &ps);
		break;
	}
	case WM_DESTROY: {
		onDestroy();
		break;
	}
	case WM_TIMER: {
		onTimer(wParam);
		break;
	}
	default:
		return DefWindowProc(m_hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CWindow::windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		return pWindow->handleMessage(message, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
