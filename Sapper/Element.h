#pragma once
#include <windows.h>

class Element
{
private:
	int colour;
	int elementValue;
	bool openedValue;
public:
	int GetColour();
	void SetColour(int value);
	void SetValue(int number);
	int GetValue();
	void SetOpened(bool b);
	bool GetOpened();
	Element();
	~Element();
};

