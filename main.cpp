#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include "MyWndClass.h"

#define RUNTIME_STATUS_FIRST 1
#define RUNTIME_STATUS_FINAL 2

#define ELEMENT_BUTTON 0
#define ELEMENT_TEXT 1

#define BUTTON_1 1
#define BUTTON_2 2

HINSTANCE hRuntimeInstance;
MY_WNDCLASS *appWindow = NULL;

int runtimeStatus = 0;

HWND hText;
HWND hButton1;
HWND hButton2;

void destroyAllElements(void)
{
  DestroyWindow(hText);
  DestroyWindow(hButton1);
  DestroyWindow(hButton2);
  return;
}

void setElement(int elementType, int elementNumber, LPCWSTR elementText, int xPos, int yPos, int width, int height)
{
  HWND parentWindow = appWindow->getWindow();
  DWORD elementStyle = (WS_CHILD | WS_VISIBLE);
  
  switch(elementType)
  {
    case ELEMENT_BUTTON:
      switch(elementNumber)
      {
        case BUTTON_1:
          hButton1 = CreateWindowEx(0, TEXT("BUTTON"), elementText, elementStyle, xPos, yPos, width, height, parentWindow, (HMENU) BUTTON_1, NULL, NULL);
          ShowWindow(hButton1, SW_SHOW);
          break;
          
        case BUTTON_2:
          hButton2 = CreateWindowEx(0, TEXT("BUTTON"), elementText, elementStyle, xPos, yPos, width, height, parentWindow, (HMENU) BUTTON_2, NULL, NULL);
          ShowWindow(hButton2, SW_SHOW);
          break;
      }
      break;
      
    case ELEMENT_TEXT:
      hText = CreateWindowEx(0, TEXT("STATIC"), elementText, elementStyle, xPos, yPos, width, height, parentWindow, NULL, NULL, NULL);
      ShowWindow(hText, SW_SHOW);
      break;
  }
  
  return;
}

void paintFirstScreen(void)
{
  destroyAllElements();
  setElement(ELEMENT_TEXT, 0, TEXT("This is First Screen"), 60, 50, 600, 20);
  setElement(ELEMENT_BUTTON, BUTTON_1, TEXT("Go To Second Screen"), 150, 200, 200, 20);
  setElement(ELEMENT_BUTTON, BUTTON_2, TEXT("Pop Message Box"), 370, 200, 200, 20);
  return;
}

void paintSecondScreen(void)
{
  destroyAllElements();
  setElement(ELEMENT_TEXT, 0, TEXT("This is Second Screen"), 60, 50, 600, 20);
  setElement(ELEMENT_BUTTON, BUTTON_1, TEXT("Go To First Screen"), 260, 200, 200, 20);
  return;
}

void popMessageBox(void)
{
  MessageBox(NULL, TEXT("Here is your message box!\n:D"), TEXT("Just a Regular Message Box"), MB_OK);
  return;
}

void initialize(void)
{
  appWindow = new MY_WNDCLASS();
  runtimeStatus = RUNTIME_STATUS_FIRST;
  paintFirstScreen();
  ShowWindow(appWindow->getWindow(), SW_SHOW);
  return;
}

void terminate(void)
{
  destroyAllElements();
  appWindow->~MY_WNDCLASS();
  return;
}

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch(msg)
  {
    case WM_CLOSE:
      PostQuitMessage(0);
      return 0;
      
    case WM_COMMAND:
      switch(runtimeStatus)
      {
        case RUNTIME_STATUS_FIRST:
          if(LOWORD(wParam) == BUTTON_1)
          {
            runtimeStatus = RUNTIME_STATUS_FINAL;
            paintSecondScreen();
            return 0;
          }
          else if(LOWORD(wParam) == BUTTON_2)
          {
            popMessageBox();
            return 0;
          }
          break;
          
        case RUNTIME_STATUS_FINAL:
          if(LOWORD(wParam) == BUTTON_1)
          {
            runtimeStatus = RUNTIME_STATUS_FIRST;
            paintFirstScreen();
            return 0;
          }
          break;
      }
      break;
  }
  
  return DefWindowProc(hWnd, msg, wParam, lParam);
}

WINBOOL runtimeContinue(void)
{
  MSG msg;
  while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    if(msg.message == WM_QUIT) return FALSE;
    
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  
  return TRUE;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
  hRuntimeInstance = hInstance;
  initialize();
  
  while(runtimeContinue()) Sleep(10);
  
  terminate();
  return 0;
}
