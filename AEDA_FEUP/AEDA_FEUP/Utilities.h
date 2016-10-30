#pragma once
#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;

bool invalidInputRetry()  // Serve para testar codigo inválido com possibilidade (input-based) de fazer retry;
{
	bool isIn = true;
	string x;
	while (isIn)
	{
		cin.clear();
		cin.ignore(1000000, '\n');
		cout << "The input was invalid. Do you wish to try again? (y/n)\n";
		cin >> x;
		if (x == "yes" || x == "y")
			return true;
		if (x == "no" || x == "n")
			isIn = false;
		else
			continue;
	}
	return false;
}

bool invalidInputNoRetry() // Serve para fazer codigo bonitinho, num ciclo while, em que não pode fazer retry
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000000, '\n');
		cout << "\n\n The input was invalid. Retrying last segment.\n\n";
		return true;
	}
	else
		return false;
}

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
};