#include <windows.h>
#include <ctime>
#include "resource.h"

#define IDC_CLEAR_BUTTON 99
#define IDC_STOCK_BUTTON 100
#define IDC_CUSTOM_BUTTON 101
#define IDC_STOCK_EDIT 102
#define IDC_CUSTOM_EDIT 103
#define BKG_CUSTOM_COLOR RGB(20, 150, 20)
#define IDC_SCROLL_BAR 500
#define HK_ABOUT 801
#define HK_EXIT 802


HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam); // Window Procedure
void AppendText(const HWND &hwnd, TCHAR *newText);
// Main Function Below
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
	const char szAppName[] = "Laboratory";
	HWND hwnd;                                  // window handle
	MSG msg;                                   // object of MSG structure
	WNDCLASSEX wndclass = { 0 };                       // a structure
	wndclass.cbSize = sizeof(wndclass);       // the size of the structure
	wndclass.style = CS_HREDRAW | CS_VREDRAW;  // window styles
	wndclass.lpfnWndProc = WndProc;           // pointer to window procedure for the window class
	wndclass.cbClsExtra = 0;                 // extra data for this class
	wndclass.cbWndExtra = 0;                 // extra data for window of this type
	wndclass.hInstance = hInstance;          // handle to application instance , winmain parameter
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));   // Large Icon (32x32) displayed in taskbar
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)); // Small Icon (16x16) top bar
	wndclass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));    // load cursor
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // background color
	wndclass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);      // menu name
	wndclass.lpszClassName = szAppName; //name to identify our class



	if (!RegisterClassEx(&wndclass))
	{
		MessageBox(NULL, "Window Creation Failed", "Error 1", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,       // extended window style
		szAppName,             // window class name
		"Laboratory Work #1",      // window caption
		WS_OVERLAPPEDWINDOW, //window style
		150,      // initial x position
		250,     // initial y position
		1024,    // intial x size
		768,   // intial y size
		NULL,           // parent window handle
		NULL,          // window menu handle
		hInstance,    // program instance handle
		NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed", "Error 2", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	RegisterHotKey(hwnd, HK_EXIT, MOD_CONTROL, 0x51);
	RegisterHotKey(hwnd, HK_ABOUT, MOD_CONTROL, 0x49);
	ShowWindow(hwnd, iCmdShow); // display window
	UpdateWindow(hwnd);        // update window

	while (GetMessage(&msg, NULL, 0, 0)>0)//while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = NULL;
	HBRUSH new_brush;
	PAINTSTRUCT ps;
	RECT rect;
	static HFONT font_arial, font;
	static int cxChar, cyChar;
	static HWND hButton0, hButton1, hButton2, hEdit1, hEdit2, hwnd_arial, hScrollBar;
	LRESULT textSize;
	static int xPos=0, xMin=0, xMax=200;
	unsigned int a = 0, b = 0, c = 0;
	switch (iMsg)
	{

	case WM_CLOSE:         // occurs when user presses ALT+F4 or clicks X icon
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CREATE:

		// buttons
		hButton1 = CreateWindow("button", ">>",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			234.6, 568, // x and y
			80, 30,  //width and height
			hwnd, (HMENU)IDC_STOCK_BUTTON,
			hInst, NULL);

		hButton2 = CreateWindow("button", "<<",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			709.2, 568,
			80, 30,
			hwnd, (HMENU)IDC_CUSTOM_BUTTON,
			hInst, NULL);

		hButton0 = CreateWindow("button", "CLEAR",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			643, 568, // x and y
			80, 30,  //width and height
			hwnd, (HMENU)IDC_CLEAR_BUTTON,
			hInst, NULL);

		//edit boxes
		hEdit1 = CreateWindow(TEXT("EDIT"), TEXT("EDIT BOX 1"), // edit window
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE,
			74.6, 100,
			400, 400,
			hwnd,
			(HMENU)IDC_STOCK_EDIT,
			NULL, NULL);

		hEdit2 = CreateWindow(TEXT("EDIT"), TEXT("EDIT BOX 2 "), // edit window
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE,
			549.3, 100,
			400, 400,
			hwnd,
			(HMENU)IDC_CUSTOM_EDIT,
			NULL, NULL);
		//******
		hScrollBar = CreateWindowEx(NULL, TEXT("SCROLLBAR"), TEXT(""),
			WS_VISIBLE | WS_CHILD | SBS_VERT,
			950, 150, 25, 200,
			hwnd, (HMENU)IDC_SCROLL_BAR, GetModuleHandle(NULL), NULL);

		SetScrollRange(hScrollBar, SB_CTL, xMin, xMax, FALSE);
		SetScrollPos(hScrollBar, SB_CTL, xPos, TRUE);

		RegisterHotKey(hwnd, HK_EXIT, MOD_CONTROL, 0x51);
		RegisterHotKey(hwnd, HK_ABOUT, MOD_CONTROL, 0x49);

		//******

		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps); //function prepares the window for painting
		font_arial = CreateFont(0, 0, 0, 0, FW_DONTCARE, false, false, false,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, FF_DONTCARE, "Arial");
		SendMessage(hwnd_arial, WM_SETFONT, WPARAM(font_arial), TRUE);
		SendMessage(hButton1, WM_SETFONT, WPARAM(font_arial), TRUE);

		SetBkMode(hdc, TRANSPARENT); // set transparent background
		GetClientRect(hwnd, &rect); // retrieves the coordinates of a window's client area
		DrawText(hdc, "\n Hello ", -1, &rect, DT_CENTER | DT_TOP);
		SetTextColor(hdc, RGB(255, 0, 0));
		DrawText(hdc, "\n \n World", -1, &rect, DT_CENTER | DT_TOP);
		EndPaint(hwnd, &ps);
		break;

	case WM_SIZE:

		cxChar = LOWORD(lParam);
		cyChar = HIWORD(lParam);

		MoveWindow(hButton0, cxChar*0.4707174, cyChar*0.739583, cxChar*0.078125, cyChar*0.0390625, TRUE);
		MoveWindow(hButton1, cxChar*0.22910156, cyChar*0.739583, cxChar*0.078125, cyChar*0.0390625, TRUE);
		MoveWindow(hButton2, cxChar*0.69257812, cyChar*0.739583, cxChar*0.078125, cyChar*0.0390625, TRUE);
		MoveWindow(hEdit1, cxChar*0.072851, cyChar*0.130208, cxChar*0.390625, cyChar*0.520834, TRUE);
		MoveWindow(hEdit2, cxChar*0.53642578, cyChar*0.130208, cxChar*0.390625, cyChar*0.520834, TRUE);
		MoveWindow(hScrollBar, cxChar*0.9457, cyChar*0.195312, cxChar*0.0300625, cyChar*0.26041, TRUE);

		break;


	case WM_GETMINMAXINFO: // set the minimum window size
	{
							   LPMINMAXINFO pInfo = (LPMINMAXINFO)lParam;
							   pInfo->ptMinTrackSize.x = 700;
							   pInfo->ptMinTrackSize.y = 500;
	}
		break;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDC_STOCK_BUTTON:
		{
								 char buffer[256];
								 SendMessage(hEdit1,
									 WM_GETTEXT,
									 sizeof(buffer) / sizeof(buffer[0]),
									 reinterpret_cast<LPARAM>(buffer));

								 //SetWindowText(GetDlgItem(hwnd,IDC_CUSTOM_EDIT),buffer);
								 AppendText(hwnd, buffer);
		}
			break;

		case WM_HOTKEY:
		{
						  switch (LOWORD(wParam))
						  {
						  case HK_ABOUT:
						  {
									 MessageBox(NULL, "Student: Gaiu Dorin \n Group: FAF-121", "About ", MB_OK);
						  }break;
						  case HK_EXIT:
						  {
												 SendMessage(hwnd, WM_DESTROY, NULL, NULL);
						  }break;
						  }
		}break;

		case IDC_CUSTOM_BUTTON:
		{
								  font = CreateFont(0, 0, 0, 0, FW_DONTCARE, false, false, false,
									  DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
									  DEFAULT_QUALITY, FF_DONTCARE, TEXT("Arial"));// creat Arial font, using default parameters
								  SendMessage(hEdit2, WM_SETFONT, (WPARAM)font, TRUE);

								  char buffer[256];
								  SendMessage(hEdit2,
									  WM_GETTEXT,
									  sizeof(buffer) / sizeof(buffer[0]),
									  reinterpret_cast<LPARAM>(buffer));

								  SetWindowText(GetDlgItem(hwnd, IDC_STOCK_EDIT), buffer);
								  UpdateWindow(hwnd);
		}
			break;

		case IDC_CLEAR_BUTTON:
		{
								 SetWindowText(GetDlgItem(hwnd, IDC_STOCK_EDIT), "");
								 SetWindowText(GetDlgItem(hwnd, IDC_CUSTOM_EDIT), "");
		}
			break;

		case ID_PROGRAM_EXIT:
		{
								PostQuitMessage(0);
		}
			break;

		case ID_ABOUT_DEVELOPER:
		{
			MessageBox(NULL, "Student: Gaiu Dorin \n Group: FAF-121", "About ", MB_OK);
		}
			break;

		case ID_BACKGROUND_YELLOW:
		{
			SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(255,255,0)));
			InvalidateRect(hwnd, NULL, TRUE);
		}

		break;

		case ID_BACKGROUND_BLUE:
		{
			SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(50, 50, 255)));
			InvalidateRect(hwnd, NULL, TRUE);
		}

			break;

		case ID_PROPERTY_DEFAULT:
		{
			SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(255, 255, 255)));
			InvalidateRect(hwnd, NULL, TRUE);
		}

			break;

	}
		break;

	case WM_CTLCOLOREDIT: // change color for edit window
	{
							  if (IDC_CUSTOM_EDIT == GetDlgCtrlID((HWND)lParam))
							  {
								  hdc = (HDC)wParam;
								  new_brush = CreateSolidBrush(BKG_CUSTOM_COLOR); // create a new color for window
								  SetBkMode((HDC)wParam, TRANSPARENT); //setting transparent background, otherwise the line
								  // where text is typing will be of default color
								  return (LONG)new_brush;
							  }

							  UpdateWindow(hwnd);
	}
		break;

	case WM_VSCROLL:
	{
					   


					   if ((HWND)lParam == hScrollBar)
					   {

						   switch (LOWORD(wParam))
						   {
						   case SB_LINEUP:
						   {

											 a = rand() % 250;
											 b = rand() % 250;
											 c = rand() % 250;
											 SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(a, b, c)));
											 InvalidateRect(hwnd, NULL, TRUE);


											   xPos -= 1;
											   break;
						   }

						   case SB_LINEDOWN:
						   {
											   MessageBox(NULL, "Student: Gaiu Dorin \n Group: FAF-121", "About ", MB_OK);
												xPos += 1;
												break;
						   }

						   case SB_PAGEUP:
						   {
											   xPos -= 10;
											   break;
						   }

						   case SB_PAGEDOWN:
						   {
										
												xPos += 10;
												break;
						   }

						   case SB_TOP:
						   {
										
										  xPos = xMin;
										  break;
						   }

						   case SB_BOTTOM:
						   {
											 
											 xPos = xMax;
											 break;
						   }

						   case SB_THUMBPOSITION:
						   {
													
													break;
						   }

						   case SB_THUMBTRACK:
						   {
											
												 break;
						   }

						   default:
							   break;

						   }
					   }



				 
	}
		break;

	case WM_SYSCOMMAND: // change behavior of different window actions
		switch (wParam)
		{

		case SC_CLOSE:

			if (MessageBox(hwnd, "Do you want to exit?", "Warning", MB_YESNO) == IDYES)
			{
				DestroyWindow(hwnd);
				UpdateWindow(hwnd);
			}

			break;

		default:

			return DefWindowProc(hwnd, iMsg, wParam, lParam);
		}
		break; // switch break
		break;

	default:
		return DefWindowProc(hwnd, iMsg, wParam, lParam);
	}
	return 0;
}

void AppendText(const HWND &hwnd, TCHAR *newText)
{
	// get edit control from dialog
	HWND hwndOutput = GetDlgItem(hwnd, IDC_CUSTOM_EDIT);

	// get the current selection
	DWORD StartPos, EndPos;
	SendMessage(hwndOutput, EM_GETSEL, reinterpret_cast<WPARAM>(&StartPos), reinterpret_cast<WPARAM>(&EndPos));

	// move the caret to the end of the text
	int outLength = GetWindowTextLength(hwndOutput);
	SendMessage(hwndOutput, EM_SETSEL, outLength, outLength);

	// insert the text at the new caret position
	SendMessage(hwndOutput, EM_REPLACESEL, TRUE, reinterpret_cast<LPARAM>(newText));

	// restore the previous selection
	SendMessage(hwndOutput, EM_SETSEL, StartPos, EndPos);
}