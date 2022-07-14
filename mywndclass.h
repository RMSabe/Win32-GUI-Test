#ifndef MYWNDCLASS_H
#define MYWNDCLASS_H

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

#define WNDCLASS_NAME "MY_WNDCLASS"

LPCWSTR getWndClassName(void);
HINSTANCE getRuntimeInstance(void);
LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void registerWndClass(void);
void unregisterWndClass(void);

#endif
