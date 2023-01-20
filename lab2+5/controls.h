#pragma once

#include "Windows.h"
#include "CommCtrl.h"
#include <string>

#define FIXCONST

typedef struct
{
	double x;
	double y;
} DIM;

typedef int (*BUTTON_ACTION)(long long initialDeposit, int durationInYears, double annualPercentage);
typedef void (*INPUTBOX_ACTION)(HWND hWnd, char *buffer);

class ControlButton
{
private:

	DIM size_;
	DIM position_;
	HWND hWnd_;
	HINSTANCE hInst_;
	const char* title_;

public:

	HWND buttonID_;
	
	ControlButton() {}

	void SetSize(double x, double y);
	void SetPosition(double x, double y);
	HWND CreateButton(HWND hWnd, HINSTANCE hInst, const char *title);
	HWND UpdateButton(void);
	void DestroyButton(void);
	void AssignAction(BUTTON_ACTION ButtonAction);
	BUTTON_ACTION ExecuteAction;

	~ControlButton(void) {}
};

class DisplayBox
{
private:

	DIM size_;
	DIM position_;
	HWND hWnd_;
	HINSTANCE hInst_;
	const char *text_;

public:

	HWND displayBoxID_;

	DisplayBox() {}

	void SetSize(double x, double y);
	void SetPosition(double x, double y);
	void SetText(const char *text);
	HWND CreateDisplayBox(HWND hWnd, HINSTANCE hInst);
	void DestroyDisplayBox(void);

	~DisplayBox(void) {}
};

class ComboBox
{
private:

	DIM size_;
	DIM position_;
	HWND hWnd_;
	HINSTANCE hInst_;
	const char **itemList_;

public:

	HWND comboBoxID_;

	ComboBox() {}

	void SetSize(double x, double y);
	void SetPosition(double x, double y);
	HWND CreateComboBox(HWND hWnd, HINSTANCE hInst);
	void AddString(const char* text);
	void DestroyComboBox(void);
	int toInt(const char *buffer);

	~ComboBox(void) {}
};

class InputBox
{
private:
	
	DIM size_;
	DIM position_;
	HWND hWnd_;
	HINSTANCE hInst_;

public:
	
	HWND inputBoxID_;
	const char *inputString;

	InputBox() {}

	void SetSize(double x, double y);
	void SetPosition(double x, double y);
	HWND CreateInputBox(HWND hWnd, HINSTANCE hInst);
	void AssignAction(INPUTBOX_ACTION InputBoxAction);
	INPUTBOX_ACTION ExecuteAction;
	long long toLong(const char *buffer);

};