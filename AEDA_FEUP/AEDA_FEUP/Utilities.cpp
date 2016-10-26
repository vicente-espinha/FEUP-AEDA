#include "Utilities.h"

//Construtor
Utilities::Utilities() {
}


bool invalidInput()
{
	bool b = true;
	while (b)
	{
		string x;
		cin.clear();
		cin.ignore(10000);
		cout << "Invalid input. Do you wish to try again? (y/n)";
		if (x == "yes" || x == "y")
			return true;
		else if (x == "no" || x == "n")
			return false;
		else
			continue;
	}
}


//Clears the console (avoids using 'system' function)
void Utilities::clearScreen() {

	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	//Gets the "buffer's" current number of cells
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	//Fills the "buffer" with ' '
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	//Sets the cursor in its initial position
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

//Changes the output color
void Utilities::setColor(int color) {

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}

//Clears cin "buffer"
void Utilities::cinClear() {
	cin.clear();
	cin.ignore(1000, '\n');
	return;
}

void Utilities::cancelMessage() {
	setColor(7); cout << "\n  WARNING: You have canceled the operation!\n           Press any key to continue... "; setColor(15);
	cinClear();
	clearScreen();
	return;
}

void Utilities::successMessage() {
	setColor(10); cout << "\n  OPERATION COMPLETED!\n"; setColor(15);
	setColor(7); cout << "\n  Press ENTER to continue... "; setColor(15);
	cinClear();
	clearScreen();
	return;
}

void Utilities::pressToContinueMessage() {
	setColor(7); cout << "\n  Press ENTER to continue... "; setColor(15);
	getchar();
	clearScreen();
	return;
}

void Utilities::aboutMessage() {
	setColor(14); cout << "\n  'A place in the Sun' is a software developed by:\n  - Diogo Dores\n  - Pedro Reis\n  - Vicente Espinha\n\n  FEUP MIEIC - 2016\n\n"; setColor(15);
	return;
}