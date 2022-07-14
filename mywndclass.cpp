#include "mywndclass.h"
#include <windows.h>

LPCWSTR getWndClassName(void)
{
  return TEXT(WNDCLASS_NAME);
}

void registerWndClass(void)
{
  return;
}
