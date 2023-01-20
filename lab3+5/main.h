#pragma once

#include "resource.h"
#include "controls.h"

#define WINDOW_SIZEX		600
#define WINDOW_SIZEY		150

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);