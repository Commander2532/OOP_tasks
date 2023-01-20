#pragma once

#include "Windows.h"
#include "CommCtrl.h"
#include <string>

#define FIXCONST
#define INPUTBOX_MAX_BUF_DEC	11
#define INPUTBOX_MAX_BUF_BIN	32
#define INPUTBOX_MAX_BUF_HEX	8

typedef struct
{
	double x;
	double y;
} DIM;

typedef int(*BUTTON_ACTION)(long long initialDeposit, int durationInYears, double annualPercentage);
typedef void(*INPUTBOX_ACTION)(HWND hWnd, char* buffer);

class InputBox
{
private:

	DIM size_;
	DIM position_;
	HWND hWnd_;
	HINSTANCE hInst_;

public:

	HWND inputBoxID_;
	const char* inputString;

	InputBox() {}

	void SetSize(double x, double y);
	void SetPosition(double x, double y);
	HWND CreateInputBox(HWND hWnd, HINSTANCE hInst);
	void SetText(const char* text);
	void GetText(char* text);
	void toString(int value, char *text, int radix);
	void AssignAction(INPUTBOX_ACTION InputBoxAction);
	INPUTBOX_ACTION ExecuteAction;
	int toInt(char* buffer);

};

char* lltoa(long long val, int raddix);