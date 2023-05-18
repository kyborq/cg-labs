#include <windows.h>
#include <vector>

#include "CGroup.h"

#pragma once
class CWindow
{
public:
	CWindow(HINSTANCE hInstance, LPCTSTR className, LPCTSTR title, int width, int height);
	~CWindow();

	void OnPaint(HDC hdc, PAINTSTRUCT ps);
	void OnDestroy();
	void OnTimer(UINT_PTR nIDEvent);
	void SetBackground(COLORREF color);

	HWND GetHWND() const;

protected:
	virtual LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	HINSTANCE m_hInstance;
	HWND m_hWnd;

	std::vector<CGroup> m_groups;
	COLORREF m_background;
};
