#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include "Utilities.h"
#include "Menu.h"

int main() {

	Utilities u;
	Menu m;

	cout << "\n  A PLACE IN THE SUN"; Sleep(1);
	cout << "\n  Find your ideal room... At the best price\n"; Sleep(1);
	cout << "\n  You will be now asked to input the name of the resource files. \n"; Sleep(1);

	u.clearScreen();
	m.LoginMenu();

	u.clearScreen();
	u.aboutMessage();
	Sleep(3000);
	return 0;
}