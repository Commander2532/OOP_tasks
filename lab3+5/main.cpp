#include "framework.h"
#include "main.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
CHAR szTitle[MAX_LOADSTRING];
CHAR szWindowClass[MAX_LOADSTRING];

Button ActionButton;
ComboBox SelectBox;
InputBox InputBox1, InputBox2;
OutputBox OutputBox1;

int xSize = WINDOW_SIZEX;
int ySize = WINDOW_SIZEY;
int xCenter = GetSystemMetrics(SM_CXSCREEN) / 2;
int yCenter = GetSystemMetrics(SM_CYSCREEN) / 2;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_LAB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));

    MSG msg;

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

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_LAB3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;
   HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   xCenter, yCenter, WINDOW_SIZEX, WINDOW_SIZEY, nullptr, nullptr, hInstance, nullptr);

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
		InputBox1.SetPosition(25, 25);
		InputBox1.SetSize(100, 30);
		InputBox1.Create(hWnd, hInst, NULL);

		InputBox2.SetPosition(200, 25);
		InputBox2.SetSize(100, 30);
		InputBox2.Create(hWnd, hInst, NULL);

		SelectBox.SetPosition(140, 29);
		SelectBox.SetSize(50, 60);
		SelectBox.Create(hWnd, hInst, NULL);
		SelectBox.SetString("|");
		SelectBox.SetString("&");
		SelectBox.SetString("^");
		SelectBox.SetString("->");

		ActionButton.SetPosition(310, 25);
		ActionButton.SetSize(50, 30);
		ActionButton.Create(hWnd, hInst, "=");

		OutputBox1.SetPosition(370, 25);
		OutputBox1.SetSize(100, 30);
		OutputBox1.Create(hWnd, hInst, NULL);

		break;
	}
    case WM_COMMAND:
        {
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				char buffer[3] = { 0 };
				SelectBox.GetString(buffer);
				buffer[0] == '|' ? ActionButton.operationCode = 1 : NULL;
				buffer[0] == '&' ? ActionButton.operationCode = 2 : NULL;
				buffer[0] == '^' ? ActionButton.operationCode = 3 : NULL;
				buffer[0] == '-' ? ActionButton.operationCode = 4 : NULL;
				break;
			}
			case EN_CHANGE:
			{
				try
				{
					if (lParam == (LPARAM)InputBox1.elementID_)
					{
						char buffer[64];
						InputBox1.GetString(buffer);
						ActionButton.firstValue = atoi(buffer);
					}
					else if (lParam == (LPARAM)InputBox2.elementID_)
					{
						char buffer[64];
						InputBox2.GetString(buffer);
						ActionButton.secondValue = atoi(buffer);
					}
				}
				catch (int a)
				{
					char debug[32];
					sprintf_s(debug, "Ошибка. Код ошибки: %d", a);
					MessageBox(hWnd, debug, "Ошибка", MB_OK | MB_ICONERROR);
				}
				break;
			}
			}
            switch (LOWORD(wParam))
            {
			case BN_CLICKED:
			{
				if (lParam == (LPARAM)ActionButton.elementID_)
				{
					try
					{
						char buffer[64];
						int result = ActionButton.Execute();
						_itoa_s(result, buffer, 10);
						OutputBox1.SetString(buffer);
					}
					catch (int a)
					{
						char debug[32];
						sprintf_s(debug, "Ошибка. Код ошибки: %d", a);
						MessageBox(hWnd, debug, "Ошибка", MB_OK | MB_ICONERROR);
					}
				}
				break;
			}
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
