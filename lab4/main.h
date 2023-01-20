#pragma once

#include "resource.h"
#include "windows.h"
#include "controls.h"
#include <math.h>

#define MAX_LOADSTRING 100

#define WND_SIZEX 550
#define WND_SIZEY 250

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

