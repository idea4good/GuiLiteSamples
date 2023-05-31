// HostMonitor.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "UiBlock.h"
#include "HostMonitor.h"
#include <windowsx.h>
#include <shellapi.h>

#define MAX_LOADSTRING 100
#define COLOR_BYTES		2
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
CUiBlock UIblock(COLOR_BYTES);

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadHostMonitor(LPVOID pParam);
DWORD WINAPI ThreadUpdateUI(LPVOID pParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HOSTMONITOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HOSTMONITOR));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
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
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HOSTMONITOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HOSTMONITOR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   
   DWORD threadID;
   CreateThread(NULL, 0, ThreadHostMonitor, NULL, 0, &threadID);
   CreateThread(NULL, 0, ThreadUpdateUI, hWnd, 0, &threadID);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here....
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_LBUTTONDOWN:
		UIblock.OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_LBUTTONUP:
		UIblock.OnLButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_MOUSEMOVE:
		UIblock.OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

//////////////////////// Host Monitor Interface ////////////////////////
int sync_data(int hr, int spo2, int rr, int nibp_sys, int nibp_dia, int nibp_mean);
typedef int(*SYNC_DATA)(int hr, int spo2, int rr, int nibp_sys, int nibp_dia, int nibp_mean);
extern SYNC_DATA gSyncData;
extern void startHostMonitor(void* phy_fb, int screen_width, int screen_height, int color_bytes);
DWORD WINAPI ThreadHostMonitor(LPVOID pParam)
{
	ShellExecute(0, L"open", L"https://github.com/idea4good/GuiLite", L"", L"", SW_SHOWNORMAL);
	gSyncData = sync_data;
	sync_data(60, 98, 30, 120, 80, 100);//Ping cloud
	startHostMonitor(calloc(1024 * 768, COLOR_BYTES), 1024, 768, COLOR_BYTES);
	return 0;
}

DWORD WINAPI ThreadUpdateUI(LPVOID pParam)
{
	Sleep(2000);//wait for host monitor initialized
	HDC hdc = GetDC((HWND)pParam);
	RECT rect;
	while (true)
	{
		GetClientRect((HWND)pParam, &rect);
		UIblock.renderUI(rect, hdc);
		Sleep(30);
	}
	return -1;
}

int sync_data(int hr, int spo2, int rr, int nibp_sys, int nibp_dia, int nibp_mean)
{
    return 0;
	wchar_t arguments[128];
	memset(arguments, 0, sizeof(arguments));
	swprintf(arguments, 128, L"/C sync_data.bat %d %d %d %d %d %d Win32",
		hr, spo2, rr, nibp_sys, nibp_dia, nibp_mean);
	HINSTANCE ret = ShellExecute(NULL, L"open", L"cmd.exe", arguments, NULL, SW_HIDE);
	return 0;
}
