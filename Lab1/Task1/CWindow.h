#include <windows.h>
#include <vector>

#include "CLetter.h"

#pragma once
class CWindow
{
public:
	CWindow(HINSTANCE hInstance, LPCTSTR className, LPCTSTR title, int width, int height);
	~CWindow();

	void onPaint(HDC hdc, PAINTSTRUCT ps);
	void onDestroy();
	void onTimer(UINT_PTR nIDEvent);

	HWND hWnd() const;

protected:
	virtual LRESULT handleMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
	static LRESULT CALLBACK windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	HINSTANCE m_hInstance;
	HWND m_hWnd;

	CLetter m_letter;
	std::vector<CLetter> m_letters;
};
