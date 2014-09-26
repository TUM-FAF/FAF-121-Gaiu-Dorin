// Lab3-WinAPI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Lab3-WinAPI.h"
#include <objidl.h>
#include <gdiplus.h>
#include <commdlg.h>
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib,"Comdlg32.lib")
using namespace Gdiplus;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
static unsigned int selectedToolIdentifier = 100;
static BOOL bFilledFlag = FALSE;
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
VOID OnPaint(HDC hdc, INT xStart, INT yStart, INT xEnd, INT yEnd, Color penColor, float penWidth, INT x3Bezier, INT y3Bezier,INT x4Bezier,INT y4Bezier);
INT GetRectangleWH(INT x1, INT x2);
COLORREF colorSelect(HWND hwnd, COLORREF color);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	//GDI
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LAB3WINAPI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3WINAPI));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);
	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3WINAPI));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LAB3WINAPI);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static float borderWidth = 5;
	static INT xStart = 0, yStart = 0, xEnd = 0, yEnd = 0 , x3Bezier = 0, y3Bezier = 0, x4Bezier = 0, y4Bezier = 0;
	static unsigned int iMouseControl = 0, iBezierMode = 0;
	static Color lineColor;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_WEIGHT_8:
			borderWidth = 8;
			break;
		case ID_WEIGHT_7:
			borderWidth = 7;
			break;
		case ID_WEIGHT_6:
			borderWidth = 6;
			break;
		case ID_WEIGHT_5:
			borderWidth = 5;
			break;
		case ID_WEIGHT_4:
			borderWidth = 4;
			break;
		case ID_TOOLS_LINE:
			selectedToolIdentifier = 1;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case ID_TOOLS_ELLIPSE:
			selectedToolIdentifier = 2;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case ID_TOOLS_RECTANGLE:
			selectedToolIdentifier = 3;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case ID_BEZIER_3POINT:
			selectedToolIdentifier = 4;
			iBezierMode = 3;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case ID_BEZIER_4POINT:
			selectedToolIdentifier = 4;
			iBezierMode = 4;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case ID_FILLCOLOR_ELLIPSE:
			bFilledFlag = ~bFilledFlag;
			break;
		case ID_FILLCOLOR_RECTANGLE:
			bFilledFlag = ~bFilledFlag;
			break;
		case ID_BORDERCOLOR_ELLIPSE:
			selectedToolIdentifier = 5;
			break;
		case ID_COLORS_LINE:
		{
							   COLORREF tempColor = colorSelect(hWnd, lineColor.ToCOLORREF());
							   lineColor.SetFromCOLORREF(tempColor);
		}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	
	case WM_PAINT:
		if (iMouseControl == 2)
		{
			hdc = GetDC(hWnd);
			OnPaint(hdc, xStart, yStart, xEnd, yEnd, lineColor, borderWidth,x3Bezier,y3Bezier,x4Bezier,y4Bezier);
			ReleaseDC(hWnd, hdc);
			iMouseControl = 0;
			SaveDC(hdc);
		}

		break;

	case WM_LBUTTONDOWN:
	{
						   switch (iMouseControl)
						   {
						   case 0:
							   xStart = LOWORD(lParam);
							   yStart = HIWORD(lParam);
							   iMouseControl = 1;
							   break;
						   case 1:
							   xEnd = LOWORD(lParam);
							   yEnd = HIWORD(lParam);
							   iMouseControl = 2;
							   break;
						   }

	}
		break;

	case WM_RBUTTONDOWN:
	{
						   switch (iBezierMode)
						   {
						   case 3:
							   x3Bezier = LOWORD(lParam);
							   y3Bezier = HIWORD(lParam);
							   x4Bezier = x3Bezier;
							   y4Bezier = y3Bezier;
							   break;
						   case 4:
							   x3Bezier = LOWORD(lParam);
							   y3Bezier = HIWORD(lParam);
							   iBezierMode = 5;
							   break;
						   case 5:
							   x4Bezier = LOWORD(lParam);
							   y4Bezier = HIWORD(lParam);
							   iBezierMode = 4;
							   break;
						   }
	}
		break;

	case WM_ERASEBKGND:
		return (LRESULT)1;
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

VOID OnPaint(HDC hdc, INT xStart, INT yStart, INT xEnd, INT yEnd, Color penColor, float penWidth, INT x3Bezier, INT y3Bezier, INT x4Bezier, INT y4Bezier)
{
	Graphics graphics(hdc);
	Pen      pen(penColor,penWidth);
	switch (selectedToolIdentifier)
	{
	case 1:
	{
			  graphics.SetSmoothingMode(SmoothingModeHighQuality);
			  graphics.DrawLine(&pen, xStart, yStart, xEnd, yEnd);
	}
		break;
	case 2:
	{
			  INT xCoord = GetRectangleWH(xEnd, xStart);
			  INT yCoord = GetRectangleWH(yEnd, yStart);
			  graphics.SetSmoothingMode(SmoothingModeHighQuality);
			  if (bFilledFlag)
			  {
				  SolidBrush *temp = new SolidBrush(penColor);
				  graphics.FillEllipse(temp, xStart, yStart, xCoord, yCoord);
			  }
			  else
			  {
				  graphics.DrawEllipse(&pen, xStart, yStart, xCoord, yCoord);
			  }		  
	}

		break;
	case 3:
	{
			  INT xCoord = GetRectangleWH(xEnd, xStart);
			  INT yCoord = GetRectangleWH(yEnd, yStart);
			  if (bFilledFlag)
			  {
				  graphics.DrawRectangle(&pen, xStart, yStart, xCoord, yCoord);
			  }
			  else
			  {
				  //SolidBrush *temp = new SolidBrush(penColor);
				  Rect tmp = Rect(xStart, yStart, xCoord, yCoord);
				  LinearGradientBrush *tempBr = new LinearGradientBrush(tmp, penColor, Color(255,0,0), 45, FALSE);
				  graphics.FillRectangle(tempBr, xStart, yStart, xCoord, yCoord);
			  }
			  
	}
		break;
	case 4:
	{
			  graphics.SetSmoothingMode(SmoothingModeHighQuality);
			  graphics.DrawBezier(&pen, xStart, yStart, x3Bezier, y3Bezier, x4Bezier, y4Bezier, xEnd, yEnd);
	}
		break;
	case 5:
	{
			  Image image(L"NiceImage.jpg");
			  graphics.DrawImage(&image, 0, 0);

	}
		break;
	}
}

INT GetRectangleWH(INT x1, INT x2)
{
	INT x = x1 - x2;
	if (x < 0)
	{
		x *= -1;
	}
	return x;
}

COLORREF colorSelect(HWND hwnd, COLORREF color)
{
	COLORREF g_rgbCustom[16] = { 0 };
	CHOOSECOLOR cc = { sizeof(CHOOSECOLOR) };

	cc.Flags = CC_RGBINIT | CC_SOLIDCOLOR;
	cc.hwndOwner = hwnd;
	cc.rgbResult = color;
	cc.lpCustColors = g_rgbCustom;

	if (ChooseColor(&cc))
	{
		color = cc.rgbResult;
	}

	return color;
}