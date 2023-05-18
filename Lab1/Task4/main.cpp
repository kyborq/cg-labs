#include <windows.h>

#include "CAWindow.h"
#include "CHangman.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CAWindow window(hInstance, TEXT("MyWindowClass"), TEXT("My Window"), 640, 480);
	CHangman hangman(window);


	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
