// Win32-Lab4.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32-Lab4.h"
#include <objidl.h>
#include <gdiplus.h>
#include <commdlg.h>
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib,"Comdlg32.lib")
using namespace Gdiplus;

#define MAX_LOADSTRING 100
#define ID_TIMER 1

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
VOID OnPaint(HWND hWnd, HDC hdc, float penWidth, Color penColor, INT *coordinatesArray);
INT GetRectangleWH(INT x1, INT x2);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//GDI
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32LAB4, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32LAB4));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

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

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32LAB4));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32LAB4);
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
      CW_USEDEFAULT, 0, 1280, 720, 0, NULL, NULL, hInstance, NULL);

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
	static BOOL hitWall = FALSE, bTransparency = FALSE;
	// rectangle:line:line:rectangle:rectangle
	static INT coordinatesArray[14] = { 0, 0, 300, 0, 300, 100, 300, 570, 300, 670, 350, 200, 1000, 100 }; 
	static float penWidth = 9;
	static byte lTransparency = 255;
	static int aSpeed = 10; // ms
	Color penColor = Color(lTransparency, 0, 255, 0);

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
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		OnPaint(hWnd, hdc, penWidth, penColor, coordinatesArray);
		EndPaint(hWnd,&ps);
		break;
	case WM_CREATE:
		SetTimer(hWnd, ID_TIMER, aSpeed, NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ERASEBKGND:
		return FALSE;
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case ID_TIMER: // every 0.01 seconds
			
			if (!hitWall)
			{
				coordinatesArray[3] += 1;
				coordinatesArray[5] += 1;

				coordinatesArray[7] -= 1;
				coordinatesArray[9] -= 1;

				coordinatesArray[10] += 1;
				coordinatesArray[12] += 1;
				if (coordinatesArray[5] == 340)
				{
					hitWall = TRUE;
				}
			}
			if (hitWall)
			{
				coordinatesArray[3] -= 1;
				coordinatesArray[5] -= 1;

				coordinatesArray[7] += 1;
				coordinatesArray[9] += 1;

				coordinatesArray[10] -= 1;
				coordinatesArray[12] -= 1;

				if (coordinatesArray[3] == 0)
				{
					hitWall = false;
				}
			}

			if (!bTransparency)
			{
				lTransparency -= 1;
				if (lTransparency == 0)
				{
					bTransparency = TRUE;
				}
			}

			if (bTransparency)
			{
				lTransparency += 1;

				if (lTransparency == 255)
				{
					bTransparency = FALSE;
				}
			}
			InvalidateRect(hWnd, 0, TRUE);
			UpdateWindow(hWnd);
			break;
		}

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RIGHT:
			coordinatesArray[0] += 10;
			break;

		case VK_LEFT:
			coordinatesArray[0] -= 10;
			break;

		case VK_UP:
			coordinatesArray[1] -= 10;
			break;

		case VK_DOWN:
			coordinatesArray[1] += 10;
			break;
		}
		break;

	case WM_MOUSEWHEEL:
		if ((short)HIWORD(wParam) < 0)
		{
			aSpeed += 10;
		}
		else
		{
			aSpeed -= 10;
			if (aSpeed < 0){ aSpeed = 1; }
		}
		KillTimer(hWnd, ID_TIMER);
		SetTimer(hWnd, ID_TIMER, aSpeed, NULL);
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

VOID OnPaint(HWND hWnd, HDC hdc, float penWidth, Color penColor, INT *coordinatesArray)
{	
	RECT rcClient;
	GetClientRect(hWnd, &rcClient);

	HDC hdcMem = CreateCompatibleDC(hdc);
	const int nMemDC = SaveDC(hdcMem);

	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);
	SelectObject(hdcMem, hBitmap);
	Graphics graphics(hdcMem);
	Pen pen(penColor, penWidth);
	SolidBrush back(Color(255, 255, 255));
	graphics.FillRectangle(&back, rcClient.left, rcClient.top, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);


	graphics.SetSmoothingMode(SmoothingModeHighSpeed);

	Image image(L"nyan_cat.png");
	graphics.DrawImage(&image, coordinatesArray[0], coordinatesArray[1]);

	graphics.DrawLine(&pen, coordinatesArray[2], coordinatesArray[3], coordinatesArray[4], coordinatesArray[5]);
	graphics.DrawLine(&pen, coordinatesArray[6], coordinatesArray[7], coordinatesArray[8], coordinatesArray[9]);

	Image image2(L"earth_png.png");
	graphics.DrawImage(&image2, coordinatesArray[10], coordinatesArray[11]);
	Image image3(L"moonx.png");
	graphics.DrawImage(&image3, coordinatesArray[12], coordinatesArray[13]);

	RECT rcClip;
	GetClipBox(hdc, &rcClip);
	BitBlt(hdc, rcClip.left, rcClip.top, rcClip.right - rcClip.left, rcClip.bottom - rcClip.top, hdcMem, rcClip.left, rcClip.top, SRCCOPY);

	RestoreDC(hdcMem, nMemDC);
	DeleteObject(hBitmap);
}