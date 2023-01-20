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

ControlButton calculate;
DisplayBox result;
InputBox deposit;
InputBox duration;
ComboBox percentage;

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
    LoadString(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_LAB2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
		CreateWindow("static", "Размер вклада (руб)", WS_CHILD | WS_VISIBLE | SS_CENTER, 25, 25, 150, 30, hWnd, NULL, hInst, NULL);
		CreateWindow("static", "Срок (лет)", WS_CHILD | WS_VISIBLE | SS_CENTER, 175, 25, 100, 30, hWnd, NULL, hInst, NULL);
		CreateWindow("static", "% годовых", WS_CHILD | WS_VISIBLE | SS_LEFT, 270, 25, 100, 30, hWnd, NULL, hInst, NULL);
		CreateWindow("static", "Результат", WS_CHILD | WS_VISIBLE | SS_LEFT, 440, 25, 100, 30, hWnd, NULL, hInst, NULL);

		deposit.SetPosition(25, 55);
		deposit.SetSize(150, 30);
		deposit.CreateInputBox(hWnd, hInst);

		duration.SetPosition(200, 55);
		duration.SetSize(50, 30);
		duration.CreateInputBox(hWnd, hInst);

		percentage.SetPosition(280, 57);
		percentage.SetSize(50, 80);
		percentage.CreateComboBox(hWnd, hInst);

		result.SetPosition(400, 55);
		result.SetSize(150, 30);
		result.CreateDisplayBox(hWnd, hInst);

		calculate.SetPosition(350, 55);
		calculate.SetSize(30, 30);
		calculate.CreateButton(hWnd, hInst, "=");
		calculate.AssignAction(CalculateDeposit);

		percentage.AddString("4");
		percentage.AddString("4.5");
		percentage.AddString("5");
		percentage.AddString("5.5");
		percentage.AddString("6");
		percentage.AddString("6.5");
		percentage.AddString("7");

		break;
	}
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
			case BN_CLICKED:
			{
				if (lParam == (LPARAM)calculate.buttonID_)
				{
					try
					{
						char buffer[64];
						if (initialDeposit <= 0 || durationInYears <= 0 || annualPercentage <= 0) throw(-4);
						int endResult = calculate.ExecuteAction(initialDeposit, durationInYears, annualPercentage);
						_itoa_s(endResult, buffer, 10);
						SetWindowText(result.displayBoxID_, buffer);
					}
					catch (int a)
					{
						MessageBox(hWnd, "Значение одного или нескольких полей является нулевым", "Ошибка", MB_OK | MB_ICONERROR | SS_CENTER);
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

			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				if (lParam == (LPARAM)deposit.inputBoxID_)
				{
					try
					{
						const char *buffer = new char[32];
						deposit.AssignAction(GetString);
						deposit.ExecuteAction(deposit.inputBoxID_, (char*)buffer);
						initialDeposit = deposit.toLong(buffer);
						if (initialDeposit < 0) throw (-1);
					}
					catch (int a)
					{
						char debug[64];
						sprintf_s(debug, "Размер вклада не должен быть отрицательным", a);
						MessageBox(hWnd, debug, "Ошибка", MB_OK | MB_ICONERROR | SS_CENTER);
						initialDeposit = 0;
					}
				}
				else if (lParam == (LPARAM)duration.inputBoxID_)
				{
					try
					{
						const char *buffer = new char[16];
						duration.AssignAction(GetString);
						duration.ExecuteAction(duration.inputBoxID_, (char*)buffer);
						durationInYears = duration.toLong(buffer);
						if (durationInYears < 0) throw (-2);
					}
					catch (int a)
					{
						char debug[64];
						sprintf_s(debug, "Длительность вклада не должна быть отрицательной", a);
						MessageBox(hWnd, debug, "Ошибка", MB_OK | MB_ICONERROR | SS_CENTER);
						durationInYears = 0;
					}
				}
				break;
			}
			case CBN_SELCHANGE:
			{
				if (lParam == (LPARAM)percentage.comboBoxID_)
				{
					char buffer[16];
					int itemIndex = SendMessage(percentage.comboBoxID_, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					SendMessage(percentage.comboBoxID_, CB_GETLBTEXT, (WPARAM)itemIndex, (LPARAM)buffer);
					std::string str = buffer;
					annualPercentage = std::stod(str);
				}
				break;
			}
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

int CalculateDeposit(long long initialDeposit, int durationInYears, double annualPercentage)
{
	double resultDeposit = initialDeposit;
	for (int i = 1; i <= durationInYears; i++)
		resultDeposit = resultDeposit + resultDeposit * (annualPercentage / 100);
	return round(resultDeposit);
}

void GetString(HWND hWnd, char* buffer)
{
	try
	{
		int n = 0;
		n = GetWindowTextLength(hWnd);
		GetWindowText(hWnd, (LPSTR)buffer, n + 1);
		for (int i = 0; i < n; i++)
			if (buffer[i] < 0x30 || buffer[i] > 0x39) throw(-3);
	}
	catch (int a)
	{
		MessageBox(hWnd, "Введенное значение должно содержать только цифры", "Ошибка", MB_OK | MB_ICONERROR | SS_CENTER);
	}
}