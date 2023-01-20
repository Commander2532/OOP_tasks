#include "framework.h"
#include "main.h"

HINSTANCE hInst;
HWND hWnd;
char szTitle[MAX_LOADSTRING];
char szWindowClass[MAX_LOADSTRING];

int xSize = WND_SIZEX;
int ySize = WND_SIZEY;
int xCenter = GetSystemMetrics(SM_CXSCREEN) / 2;
int yCenter = GetSystemMetrics(SM_CYSCREEN) / 2;

InputBox BinaryNumber;
InputBox DecimalNumber;
InputBox HexNumber;

long long initialDeposit;
int durationInYears;
double annualPercentage;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LAB45, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB45));

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB45));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_LAB45);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		((GetSystemMetrics(SM_CXSCREEN) - xSize) / 2),
		((GetSystemMetrics(SM_CYSCREEN) - ySize) / 2),
		xSize,
		ySize,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		CreateWindow("static", "Число в десятичной системе:", WS_CHILD | WS_VISIBLE | SS_CENTER, 25, 25, 150, 40, hWnd, NULL, hInst, NULL);
		CreateWindow("static", "Число в двоичной системе:", WS_CHILD | WS_VISIBLE | SS_CENTER, 25, 75, 150, 40, hWnd, NULL, hInst, NULL);
		CreateWindow("static", "Число в шестнадцатеричной системе:", WS_CHILD | WS_VISIBLE | SS_CENTER, 25, 125, 150, 50, hWnd, NULL, hInst, NULL);

		DecimalNumber.SetPosition(200, 25);
		DecimalNumber.SetSize(300, 40);
		DecimalNumber.CreateInputBox(hWnd, hInst);

		BinaryNumber.SetPosition(200, 75);
		BinaryNumber.SetSize(300, 40);
		BinaryNumber.CreateInputBox(hWnd, hInst);

		HexNumber.SetPosition(200, 125);
		HexNumber.SetSize(300, 40);
		HexNumber.CreateInputBox(hWnd, hInst);

		break;
	}
	case WM_COMMAND:
	{
		switch (HIWORD(wParam))
		{
		case EN_CHANGE:
		{
			if (lParam == (LPARAM)DecimalNumber.inputBoxID_)
			{
				try
				{
					static char buffer_dec[INPUTBOX_MAX_BUF_DEC + 1];
					char buffer_bin[32];
					char buffer_hex[32];
					DecimalNumber.GetText(buffer_dec);
					int value = DecimalNumber.toInt(buffer_dec);
					BinaryNumber.toString(value, buffer_bin, 2);
					BinaryNumber.SetText(buffer_bin);
					HexNumber.toString(value, buffer_hex, 16);
					HexNumber.SetText(buffer_hex);
				}
				catch (int a)
				{
					char debug[32];
					sprintf_s(debug, "Ошибка. Код ошибки: %d", a);
					MessageBox(hWnd, debug, "Ошибка", MB_OK | MB_ICONERROR | SS_CENTER);
				}
			}
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		switch (LOWORD(wParam))
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}