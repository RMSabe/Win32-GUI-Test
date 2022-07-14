#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

#define RUNTIME_STATUS_FIRST 1
#define RUNTIME_STATUS_FINAL 2

#define __WNDCLASS_NAME "MY_WNDCLASS"

#define __WINDOW_NAME "Win32 GUI Test"
#define WINDOW_X_POS 50
#define WINDOW_Y_POS 50
#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 360

#define ELEMENT_BUTTON 0
#define ELEMENT_TEXT 1

#define BUTTON_1 1
#define BUTTON_2 2

LPCWSTR WNDCLASS_NAME = TEXT(__WNDCLASS_NAME);
LPCWSTR WINDOW_NAME = TEXT(__WINDOW_NAME);
HINSTANCE hRuntimeInstance;
int runtimeStatus = 0;

HWND hWindow;
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
  DWORD elementStyle = (WS_CHILD | WS_VISIBLE);
  
  switch(elementType)
  {
    case ELEMENT_BUTTON:
      switch(elementNumber)
      {
        case BUTTON_1:
          hButton1 = CreateWindow(TEXT("BUTTON"), elementText, elementStyle, xPos, yPos, width, height, hWindow, (HMENU) BUTTON_1, hRuntimeInstance, NULL);
          ShowWindow(hButton1, SW_SHOW);
          break;
          
        case BUTTON_2:
          hButton2 = CreateWindow(TEXT("BUTTON"), elementText, elementStyle, xPos, yPos, width, height, hWindow, (HMENU) BUTTON_2, hRuntimeInstance, NULL);
          ShowWindow(hButton2, SW_SHOW);
          break;
      }
      break;
      
    case ELEMENT_TEXT:
      hText = CreateWindow(TEXT("STATIC"), elementText, elementStyle, xPos, yPos, width, height, hWindow, NULL, hRuntimeInstance, NULL);
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

void createMainWindow(void)
{
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
  
  hWindow = CreateWindow(WNDCLASS_NAME, WINDOW_NAME, windowStyle, xPos, yPos, width, height, NULL, NULL, hRuntimeInstance, NULL);
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

void registerWndClass(void)
{
  WNDCLASS myWndClass;
  ZeroMemory(&myWndClass, sizeof(WNDCLASS));
  myWndClass.hInstance = hRuntimeInstance;
  myWndClass.lpszClassName = WNDCLASS_NAME;
  myWndClass.lpfnWndProc = windowProcedure;
  myWndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  myWndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  myWndClass.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
  RegisterClass(&myWndClass);
  return;
}

void unregisterWndClass(void)
{
  UnregisterClass(WNDCLASS_NAME, hRuntimeInstance);
  return;
}

void initialize(void)
{
  runtimeStatus = RUNTIME_STATUS_FIRST;
  registerWndClass();
  createMainWindow();
  paintFirstScreen();
  ShowWindow(hWindow, SW_SHOW);
  return;
}

void terminate(void)
{
  destroyAllElements();
  DestroyWindow(hWindow);
  unregisterWndClass();
  return;
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
