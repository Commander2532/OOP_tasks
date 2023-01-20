#include "controls.h"

void InputBox::SetSize(double x, double y)
{
	size_.x = x;
	size_.y = y;
}

void InputBox::SetPosition(double x, double y)
{
	position_.x = x;
	position_.y = y;
}

HWND InputBox::CreateInputBox(HWND hWnd, HINSTANCE hInst)
{
	if (inputBoxID_ != NULL)
		DestroyWindow(inputBoxID_);
	hWnd_ = hWnd;
	hInst_ = hInst;
	inputBoxID_ = CreateWindow(WC_EDIT, NULL, ES_LEFT | WS_BORDER | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, position_.x, position_.y, size_.x, size_.y, hWnd_, NULL, hInst_, NULL);
	return inputBoxID_;
}

void InputBox::SetText(const char* text)
{
	SetWindowText(inputBoxID_, text);
}

void InputBox::GetText(char* text)
{
	int n;

	n = GetWindowTextLength(inputBoxID_);
	if (n > INPUTBOX_MAX_BUF_DEC) throw (-1);
	GetWindowText(inputBoxID_, text, n + 1);
}

int InputBox::toInt(char* buffer)
{
	return atoi(buffer);
}

void InputBox::toString(int value, char *text, int radix)
{
	char buf[32] = { 0 };
	if (radix != 2 && radix != 10 && radix != 16) throw(-2);
	if (value < 0) throw(-3);
	_itoa_s(value, buf, radix);
	for (int i = 0; i < sizeof(buf); i++)
		text[i] = buf[i];
}

void InputBox::AssignAction(INPUTBOX_ACTION InputBoxAction)
{
	ExecuteAction = InputBoxAction;
}

char* lltoa(long long val, int radix)
{
	static char buf[64] = { 0 };

	int i = 62;
	int sign = (val < 0);
	if (sign) val = -val;

	if (val == 0) return (char*)"0";

	for (; val && i; --i, val /= radix) {
		buf[i] = "0123456789abcdef"[val % radix];
	}

	if (sign) {
		buf[i--] = '-';
	}
	return &buf[i + 1];
}