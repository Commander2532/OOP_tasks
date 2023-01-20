#pragma once

#include "Windows.h"
#include "CommCtrl.h"
#include <string>

typedef struct
{
	int x;
	int y;
} DIM;

class InterfaceElement
{
protected:
	DIM size_;
	DIM position_;
	HWND hWnd_;
	HINSTANCE hInst_;
public:
	HWND elementID_;
	
	InterfaceElement() {}
	virtual ~InterfaceElement() {}
	virtual void SetPosition(int x, int y);
	virtual void SetSize(int x, int y);
	virtual void GetString(const char *text);
	virtual int Execute(void);
};

class Button : public InterfaceElement
{
public:
	int firstValue, secondValue, operationCode;

	Button() : InterfaceElement() {};
	void Create(HWND hWnd, HINSTANCE hInst, const char *name);
	int Execute(void);
};

class ComboBox : public InterfaceElement
{
public:
	ComboBox() : InterfaceElement() {};
	void Create(HWND hWnd, HINSTANCE hInst, const char *name);
	void SetString(const char *text);
};

class InputBox : public InterfaceElement
{
public:
	InputBox() : InterfaceElement() {};
	void Create(HWND hWnd, HINSTANCE hInst, const char *name);
};

class OutputBox : public InterfaceElement
{
public:
	OutputBox() : InterfaceElement() {};
	void Create(HWND hWnd, HINSTANCE hInst, const char *name);
	void SetString(const char *text);
};