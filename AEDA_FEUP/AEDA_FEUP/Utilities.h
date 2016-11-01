#pragma once
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <string>

using namespace std;

class Utilities {

public:
	Utilities();
	void clearScreen();
	void setColor(int x); //Altera as cores dos outputs da consola
	void cinClear();
	void cancelMessage();
	void successMessage();
	void pressToContinueMessage();
	void aboutMessage();
	bool invalidInputRetry();
	bool invalidInputNoRetry();
	string trim(string s);
};