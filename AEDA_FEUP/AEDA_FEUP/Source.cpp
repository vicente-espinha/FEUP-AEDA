#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include "Utilities.h"
#include "Menu.h"

int main() {

	Utilities u;
	Menu m;

	m.LoginMenu();

	u.clearScreen();
	u.aboutMessage();
	Sleep(3000);
	return 0;
}