#include <windows.h>
#include <vector>

#include "CFigure.h"

#pragma once
class CAWindow
{
public:
	CAWindow(HINSTANCE hInstance, LPCTSTR className, LPCTSTR title, int width, int height);
	~CAWindow();

	virtual void Start(HDC hdc) {};
	virtual void Update() {};

	HWND GetHWND() const;
	HINSTANCE GetHInstance() const;
	LPCTSTR GetClassNameW() const;
	LPCTSTR	GetTitle() const;
	int GetWidth() const;
	int GetHeight() const;

protected:
	virtual LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void OnPaint(HDC hdc, PAINTSTRUCT ps);
	void OnDestroy();
	void OnTimer(UINT_PTR nIDEvent);

	HINSTANCE m_hInstance;
	HWND m_hWnd;
};

