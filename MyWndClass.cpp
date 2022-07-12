#include "MyWndClass.h"
#include <windows.h>

LPCWSTR MY_WNDCLASS::getWndClassName(void)
{
  return WNDCLASS_NAME;
}

HINSTANCE MY_WNDCLASS::getInstance(void)
{
  return hInstance;
}

HWND MY_WNDCLASS::getWindow(void)
{
  return hWindow;
}

MY_WNDCLASS::MY_WNDCLASS(void)
{
  WNDCLASS myWndClass;
  ZeroMemory(&myWndClass, sizeof(WNDCLASS));
  myWndClass.hInstance = hInstance;
  myWndClass.lpszClassName = WNDCLASS_NAME;
  myWndClass.lpfnWndProc = windowProcedure;
  myWndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  myWndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  myWndClass.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
  RegisterClass(&myWndClass);
  
  LPCWSTR WINDOW_NAME = TEXT("Win32 GUI Test");
  DWORD windowStyle = (WS_CAPTION | WS_VISIBLE | WS_SYSMENU | WS_OVERLAPPED);
  RECT rectangle = {
    .left = WINDOW_X_POS,
    .top = WINDOW_Y_POS,
    .right = WINDOW_X_POS + WINDOW_WIDTH,
    .bottom = WINDOW_Y_POS + WINDOW_HEIGHT
  };
  AdjustWindowRect(&rectangle, windowStyle, FALSE);
  
  int xPos = rectangle.left;
  int yPos = rectangle.top;
  int width = rectangle.right - rectangle.left;
  int height = rectangle.bottom - rectangle.top;
  
  hWindow = CreateWindowEx(0, WNDCLASS_NAME, WINDOW_NAME, windowStyle, xPos, yPos, width, height, NULL, NULL, hInstance, NULL);
}

MY_WNDCLASS::~MY_WNDCLASS(void)
{
  DestroyWindow(hWindow);
  UnregisterClass(WNDCLASS_NAME, hInstance);
}
