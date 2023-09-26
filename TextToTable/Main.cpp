//#include <Windows.h>
//#include "TextToTable.h"
//#include "tableMash.h"
//#include "TableCell.h"
//
//const int M = 5;
//const int N = 5;
//WCHAR UserInput[] = L"Test1234";
//TableMash* tm;
//TableCell table[M][N];
//HINSTANCE hInst;
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//
//
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	UNREFERENCED_PARAMETER(lParam);
//	switch (message)
//	{
//	case WM_INITDIALOG:
//		return (INT_PTR)TRUE;
//
//	case WM_COMMAND:
//		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//		{
//			EndDialog(hDlg, LOWORD(wParam));
//			return (INT_PTR)TRUE;
//		}
//		break;
//	}
//	return (INT_PTR)FALSE;
//}
//
//LRESULT CALLBACK WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//	switch (uMsg) {
//	case WM_COMMAND:
//	{
//		int wmId = LOWORD(wParam);
//		// Parse the menu selections:
//		switch (wmId)
//		{
//		case IDM_ABOUT:
//			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//
//			//tm->DrawCircle(100, 100, 50, 0, 0, 0, 1);
//			break;
//		case IDM_EXIT:
//			DestroyWindow(hWnd);
//			break;
//		default:
//			return DefWindowProc(hWnd, uMsg, wParam, lParam);
//		}
//	}
//	break;
	//case WM_CREATE:
	//{
	//	tm = new TableMash();
	//	if (!(tm->Init(hWnd)))
	//	{
	//		delete tm;
	//		return 0;
	//	}
	//	tm->CreateTextFactory(hWnd,UserInput, 8);
	//	return 0;
	//}
//	case WM_SIZE:
//		tm->UpdateMesh(hWnd, table);
//		return 0;
//	case WM_PAINT:
		////Render
		//tm->BeginDraw();
		//tm->ClearScreen(1, 1, 1);
		//tm->DrawAllRect(table, UserInput, 8);
		//tm->EndDraw();
//		return 0;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	}
//
//	return DefWindowProc(hWnd, uMsg, wParam, lParam);
//}
//
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
//{
//	const wchar_t ClassName[] = L"TableWindow";
//	WNDCLASS wc = {};
//  wc.style = CS_HREDRAW | CS_VREDRAW;
// 
//	wc.lpfnWndProc = WindowProc;
//	wc.hInstance = hInstance;
//	wc.lpszClassName = ClassName;
//	wc.lpszMenuName = MAKEINTRESOURCEW(IDC_TEXTTOTABLE);
//
//
//	RegisterClass(&wc);
//
//	hInst = hInstance;
//
//	HWND hWnd = CreateWindowEx(0, ClassName, L"TextToTable", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
//
//	if (hWnd == NULL) {
//		return 0;
//	}
//
//	ShowWindow(hWnd, nCmdShow);
//
//	MSG msg = {};
//	while (GetMessage(&msg, NULL, 0, 0)) {
//		tm->UpdateMesh(hWnd, table);
//		DispatchMessage(&msg);
//	}
//
//	return 0;
//}