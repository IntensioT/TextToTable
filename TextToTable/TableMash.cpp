#include "tableMash.h"
#include <dwrite.h>
#include <cmath>

IDWriteFactory* pDWriteFactory;
IDWriteTextLayout* pTextLayout;
IDWriteTextFormat* pTextFormat;


TableMash::TableMash()
{
	pFactory = NULL;
	pRenderTarget = NULL;
	pBlackBrush = NULL;
	pTextLayout = NULL;
	pDWriteFactory = NULL;
	pTextFormat = NULL;
	brush = NULL;

}

TableMash::~TableMash()
{
	if (pFactory) pFactory->Release(); //Com interfaces should be releasesd
	if (pRenderTarget) pRenderTarget->Release();
	if (pBlackBrush) pBlackBrush->Release();
	if (pTextLayout) pTextLayout->Release();
	if (pDWriteFactory) pDWriteFactory->Release();
	if (pTextFormat) pTextFormat->Release();
	if (brush) brush->Release();
}

bool TableMash::Init(HWND windowHandle)
{
	res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
	if (res != S_OK)
	{
		return false;
	}

	RECT rect;
	GetClientRect(windowHandle, &rect);
	

	res = pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&pRenderTarget);

	if (res != S_OK)
	{
		return false;
	}

	res = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBlackBrush);

	if (res != S_OK)
	{
		return false;
	}

	res = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);

	if (res != S_OK)
	{
		return false;
	}

	return true;
}

void TableMash::ClearScreen(float r, float g, float b)
{
	pRenderTarget->Clear(D2D1::ColorF(r, g, b));
}

void TableMash::UpdateMesh(HWND windowHandle, TableCell(&table)[5][5])
{
	RECT rect;
	GetClientRect(windowHandle, &rect);
	pRenderTarget->Resize(D2D1::SizeU(rect.right, rect.bottom));
	long cellWidth = (rect.right - rect.left) / 5.0;
	long cellHeight = (rect.bottom - rect.top) / 5.0;
	long curLeft = rect.left, curTop = rect.top;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			table[i][j].ChangeRect(curLeft, curLeft+cellWidth, curTop, curTop+cellHeight);
			curLeft += cellWidth;

		}
		curLeft = rect.left;
		curTop += cellHeight;
	}
}


void TableMash::DrawAllRect(TableCell table[5][5], WCHAR text1[], int textSize)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			D2D1_RECT_F rectangle = D2D1::RectF(table[i][j].GetLeft(), table[i][j].GetTop(), table[i][j].GetRight(), table[i][j].GetBottom());

			// Draw the outline of a rectangle.
			pRenderTarget->DrawRectangle(&rectangle, pBlackBrush);


			DWRITE_TEXT_RANGE textRange = { 0, textSize };

			pTextLayout->SetFontSize(sqrt((((table[i][j].GetRight() - table[i][j].GetLeft()))^2) + ((table[i][j].GetBottom() - table[i][j].GetTop()))^2), textRange);
			pTextLayout->SetMaxWidth(table[i][j].GetRight() - table[i][j].GetLeft());
			pTextLayout->SetMaxHeight(table[i][j].GetBottom() - table[i][j].GetTop());
			pRenderTarget->DrawTextLayout(D2D1::Point2F(table[i][j].GetLeft(), table[i][j].GetTop()),pTextLayout,pBlackBrush);
		}
	}
		
	
}

HRESULT TableMash::CreateTextFactory(HWND hWnd, WCHAR text1[], int textSize)
{
	static const WCHAR msc_fontName[] = L"Verdana";
	static const FLOAT msc_fontSize = 20;
	
	if (SUCCEEDED(res))
	{
		// Create a DirectWrite factory.
		res = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(pDWriteFactory),
			reinterpret_cast<IUnknown**>(&pDWriteFactory)
		);
	}
	if (SUCCEEDED(res))
	{
		// Create a DirectWrite text format object.
		res = pDWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&pTextFormat
		);
	}


	if (SUCCEEDED(res))
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		float width = rect.right / 5;
		float height = rect.bottom / 5;

		res = pDWriteFactory->CreateTextLayout(
			text1,      // The string to be laid out and formatted.
			textSize,  // The length of the string.
			pTextFormat,  // The text format to apply to the string (contains font information, etc).
			width,         // The width of the layout box.
			height,        // The height of the layout box.
			&pTextLayout  // The IDWriteTextLayout interface pointer.
		);
	}

		if (SUCCEEDED(res))
	{
		// Center the text horizontally and vertically.
		pTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		pTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	
	return res;
}

void TableMash::DrawCircle(HWND hWnd, float x, float y, float radius, float r, float g, float b, float a)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	float width = (rect.right / M) / 13;
	float height = (rect.bottom / N) /13;
	const wchar_t madein[14] = L"Made in BSUIR";
	float diam = x + radius;
	//float letterWidthX = (x + radius)/13;
	float letterWidthX = 40;
	//float letterHeightY = (y + radius)/13;
	float letterHeightY = 40;
	float rot = 0;
	float letterX = x;
	float letterY = y - radius;

	for (int i = 0; i < 6; i++)
	{
		//const wchar_t test[1] = { madein[i]};
		if (SUCCEEDED(res))
		{
			res = pDWriteFactory->CreateTextLayout(
				L"M",      // The string to be laid out and formatted.
				1,  // The length of the string.
				pTextFormat,  // The text format to apply to the string (contains font information, etc).
				width,         // The width of the layout box.
				height,        // The height of the layout box.
				&pTextLayout  // The IDWriteTextLayout interface pointer.
			);
		}
		// fmod((x+letterWidthX), diam)
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(rot, D2D1::Point2F(letterX, letterY)));
		pRenderTarget->DrawTextLayout(D2D1::Point2F(letterX, letterY), pTextLayout, pBlackBrush);
		
		if ((letterX + letterWidthX) > diam)
		{
			letterWidthX = 0 - letterWidthX;
		}
		letterX += letterWidthX;

		if ((letterY + letterHeightY) > diam)
		{
			letterHeightY = 0 - letterHeightY;
		}
		letterY += letterHeightY;
		rot += 27.69f;
	}

	

	

	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(0.0f, D2D1::Point2F(x, y - radius)));

	brush->SetColor(D2D1::ColorF(r, g, b, a));
	pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2(x, y), radius, radius), brush, 3.0f);
}

