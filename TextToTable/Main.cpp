#include <Windows.h>
#include "TextToTable.h"
#include "tableMash.h"
#include "TableCell.h"

const int M = 5;
const int N = 5;
WCHAR UserInput[] = L"Test1234";
TableMash* tm;
TableCell table[M][N];


LRESULT CALLBACK WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
	{
		tm = new TableMash();
		if (!(tm->Init(hWnd)))
		{
			delete tm;
			return 0;
		}
		tm->CreateTextFactory(hWnd,UserInput, 8);
		return 0;
	}
	case WM_SIZE:
		tm->UpdateMesh(hWnd, table);
		return 0;
	case WM_PAINT:
		//Render
		tm->BeginDraw();
		tm->ClearScreen(1, 1, 1);
		tm->DrawAllRect(table, UserInput, 8);
		tm->EndDraw();
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	const wchar_t ClassName[] = L"TableWindow";
	WNDCLASS wc = {};
  wc.style = CS_HREDRAW | CS_VREDRAW;
 
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = ClassName;
	wc.lpszMenuName = MAKEINTRESOURCEW(IDC_TEXTTOTABLE);

	RegisterClass(&wc);

	HWND hWnd = CreateWindowEx(0, ClassName, L"TextToTable", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL) {
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		tm->UpdateMesh(hWnd, table);
		DispatchMessage(&msg);
	}

	return 0;
}