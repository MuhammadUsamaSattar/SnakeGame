#pragma once

class Menu
{
private:
	int _pointer;

public:
	void setPointer(int i);
	int getPointer();
	void navigateMenu();
	bool confirmOption();
	bool pauseCheck();
};