#ifndef MY_WNDCLASS_H
#define MY_WNDCLASS_H

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

#define WINDOW_X_POS 50
#define WINDOW_Y_POS 50
#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 360

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class MY_WNDCLASS
{
  public:
    MY_WNDCLASS(void);
    ~MY_WNDCLASS(void);
    LPCWSTR getWndClassName(void);
    HINSTANCE getInstance(void);
    HWND getWindow(void);
    
  private:
    LPCWSTR WNDCLASS_NAME = TEXT("MY_WNDCLASS");
    HINSTANCE hInstance;
    HWND hWindow;
};

#endif
