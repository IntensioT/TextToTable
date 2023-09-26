#pragma once

#include <Windows.h>
#include <d2d1.h>
#include "TableCell.h"

#define M 5
#define N 5

class TableMash
{

	ID2D1Factory* pFactory;
	//IDWriteFactory* m_pDWriteFactory;
	//IDWriteTextFormat* m_pTextFormat;


	ID2D1HwndRenderTarget* pRenderTarget; //представляет целевой объект отрисовки.
	ID2D1HwndRenderTarget* pRenderTargetEmblem; //представляет целевой объект отрисовки.
	ID2D1SolidColorBrush* pBlackBrush;
	ID2D1SolidColorBrush* brush; // представляет кисть.


	HRESULT res;

public:
	bool Init(HWND windowHandle);

	void BeginDraw() { pRenderTarget->BeginDraw(); }
	void EndDraw() { pRenderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	void UpdateMesh(HWND windowHandle, TableCell (&table)[5][5]);
	void DrawAllRect(TableCell table[5][5], WCHAR text1[], int textSize);
	HRESULT CreateTextFactory(HWND hWnd, WCHAR text1[], int textSize);
	void DrawCircle(HWND hWnd, float x, float y, float radius, float r, float g, float b, float a);



	TableMash();
	~TableMash();
};