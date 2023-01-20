#include "controls.h"

void ControlButton::SetSize(double x, double y)
{
	size_.x = x;
	size_.y = y;
}

void ControlButton::SetPosition(double x, double y)
{
	position_.x = x;
	position_.y = y;
}

HWND ControlButton::CreateButton(HWND hWnd, HINSTANCE hInst, const char *title)
{
	if (buttonID_ != NULL)
		DestroyWindow(buttonID_);
	hWnd_ = hWnd;
	hInst_ = hInst;
	buttonID_ = CreateWindow("button", title, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, position_.x, position_.y, size_.x, size_.y, hWnd_, NULL, hInst_, NULL);
	return buttonID_;
}

HWND ControlButton::UpdateButton(void)
{
	if (buttonID_ != NULL)
		DestroyWindow(buttonID_);
	buttonID_ = CreateWindow("button", title_, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, position_.x, position_.y, size_.x, size_.y, hWnd_, NULL, hInst_, NULL);
	return buttonID_;
}

void ControlButton::DestroyButton(void)
{
	if (buttonID_ != NULL)
		DestroyWindow(buttonID_);
	buttonID_ = NULL;
}

void ControlButton::AssignAction(BUTTON_ACTION ButtonAction)
{
	ExecuteAction = ButtonAction;
}

void DisplayBox::SetSize(double x, double y)
{
	size_.x = x;
	size_.y = y;
}

void DisplayBox::SetPosition(double x, double y)
{
	position_.x = x;
	position_.y = y;
}

HWND DisplayBox::CreateDisplayBox(HWND hWnd, HINSTANCE hInst)
{
	if (displayBoxID_ != NULL)
		DestroyWindow(displayBoxID_);
	hWnd_ = hWnd;
	hInst_ = hInst;
	displayBoxID_ = CreateWindow(WC_STATIC, NULL, WS_CHILD | WS_BORDER | WS_VISIBLE, position_.x, position_.y, size_.x, size_.y, hWnd_, NULL, hInst_, NULL);
	return displayBoxID_;
}

void DisplayBox::DestroyDisplayBox(void)
{
	if (displayBoxID_ != NULL)
		DestroyWindow(displayBoxID_);
	displayBoxID_ = NULL;
}

void ComboBox::SetSize(double x, double y)
{
	size_.x = x;
	size_.y = y;
}

void ComboBox::SetPosition(double x, double y)
{
	position_.x = x;
	position_.y = y;
}

HWND ComboBox::CreateComboBox(HWND hWnd, HINSTANCE hInst)
{
	if (comboBoxID_ != NULL)
		DestroyWindow(comboBoxID_);
	hWnd_ = hWnd;
	hInst_ = hInst;
	comboBoxID_ = CreateWindow(WC_COMBOBOX, NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL, position_.x, position_.y, size_.x, size_.y, hWnd_, NULL, hInst_, NULL);
	return comboBoxID_;
}

void ComboBox::AddString(const char* text)
{
	SendMessage(comboBoxID_, CB_ADDSTRING, WPARAM(0), (LPARAM)text);
}

void ComboBox::DestroyComboBox(void)
{
	if (comboBoxID_ != NULL)
		DestroyWindow(comboBoxID_);
	comboBoxID_ = NULL;
}

int ComboBox::toInt(const char *buffer)
{
	return atoi(buffer);
}

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

long long InputBox::toLong(const char *buffer)
{
	long long value = atoll(buffer);
	return value;
}

void InputBox::AssignAction(INPUTBOX_ACTION InputBoxAction)
{
	ExecuteAction = InputBoxAction;
}