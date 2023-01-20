#include "controls.h"

void InterfaceElement::SetPosition(int x, int y)
{
	position_.x = x;
	position_.y = y;
}

void InterfaceElement::SetSize(int x, int y)
{
	size_.x = x;
	size_.y = y;
}

int InterfaceElement::Execute(void)
{
	throw(1);
}

void InterfaceElement::GetString(const char *text)
{
	int n = SendMessage(elementID_, WM_GETTEXTLENGTH, NULL, NULL);
	SendMessage(elementID_, WM_GETTEXT, (WPARAM)n + 1, (LPARAM)text);
	for (int i = 0; i < n; i++)
		if ((text[i] < 0x30 || text[i] > 0x39) && (text[i] != '|' && text[i] != '&' && text[i] != '^' && text[i] != '-' && text[i] != '>')) throw(2);
	static HWND staticID;
	DestroyWindow(staticID);
	staticID = 0;
	switch (text[0])
	{
	case 0x7C:
		staticID = CreateWindow(WC_STATIC, "Выбрана операция \"OR\" ( | )", WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 25, 60, 300, 30, hWnd_, NULL, hInst_, NULL);
		break;
	case 0x26:
		staticID = CreateWindow(WC_STATIC, "Выбрана операция \"AND\" ( & )", WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 25, 60, 300, 30, hWnd_, NULL, hInst_, NULL);
		break;
	case 0x5E:
		staticID = CreateWindow(WC_STATIC, "Выбрана операция \"XOR\" ( ^ )", WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 25, 60, 300, 30, hWnd_, NULL, hInst_, NULL);
		break;
	case 0x2D:
		staticID = CreateWindow(WC_STATIC, "Выбрана операция \"NAND\" ( -> )", WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 25, 60, 300, 30, hWnd_, NULL, hInst_, NULL);
		break;
	}
}

void Button::Create(HWND hWnd, HINSTANCE hInst, const char *name)
{
	hWnd_ = hWnd;
	hInst_ = hInst;
	elementID_ = CreateWindow(WC_BUTTON, name, BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, position_.x, position_.y, size_.x, size_.y, hWnd, NULL, hInst, NULL);
}

int Button::Execute(void)
{
	if (firstValue < 0 || secondValue < 0) throw(3);
	switch (operationCode)
	{
	case 1:
		return (firstValue | secondValue);
	case 2:
		return (firstValue & secondValue);
	case 3:
		return (firstValue ^ secondValue);
	case 4:
		return (~(firstValue & secondValue));
	default:
		throw(4);
	}
}

void ComboBox::Create(HWND hWnd, HINSTANCE hInst, const char *name)
{
	hWnd_ = hWnd;
	hInst_ = hInst;
	elementID_ = CreateWindow(WC_COMBOBOX, name, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_OVERLAPPED | WS_VSCROLL | WS_CHILD | WS_VISIBLE, position_.x, position_.y, size_.x, size_.y, hWnd, NULL, hInst, NULL);
}

void ComboBox::SetString(const char *text)
{
	SendMessage(elementID_, CB_ADDSTRING, (WPARAM)0, (LPARAM)text);
}

void InputBox::Create(HWND hWnd, HINSTANCE hInst, const char *name)
{
	hWnd_ = hWnd;
	hInst_ = hInst;
	elementID_ = CreateWindow(WC_EDIT, name, WS_BORDER | WS_CHILD | WS_VISIBLE, position_.x, position_.y, size_.x, size_.y, hWnd, NULL, hInst, NULL);
}

void OutputBox::Create(HWND hWnd, HINSTANCE hInst, const char *name)
{
	hWnd_ = hWnd;
	hInst_ = hInst;
	elementID_ = CreateWindow(WC_STATIC, name, WS_BORDER | WS_CHILD | WS_VISIBLE, position_.x, position_.y, size_.x, size_.y, hWnd, NULL, hInst, NULL);
}

void OutputBox::SetString(const char *text)
{
	SendMessage(elementID_, WM_SETTEXT, (WPARAM)0, (LPARAM)text);
}