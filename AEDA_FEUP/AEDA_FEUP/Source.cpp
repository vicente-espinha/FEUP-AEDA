#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include "Utilities.h"
#include "Menu.h"
#include "Corporation.h"

Corporation* Corporation::singleton_instance = 0;

int main() {

	string usersFile, suppliersFile, saveChanges;

	//Objetos da classe. 
	Menu menu;
	Utilities u;

	u.setColor(15); u.logo();
	cout << "\n  In order to ensure the software runs as expected, an initial setup is necessary.\n"; Sleep(1);
	cout << "\n  You will be now asked to input the name of the resource files. \n"; Sleep(1);

	//CLIENTS FILE TEST (FOUND/VALID)
	cout << "\n  Users file:  ";
	u.setColor(14); getline(cin, usersFile); u.setColor(15);

	if (cin.eof()) {
		u.cancelMessage();
		return 0;
	}

	if (!(Corporation::instance()->foundUsersFile(usersFile))) {
		return 0;
	}

	Corporation::instance()->loadUsers();

	u.clearScreen();
	menu.LoginMenu();

	u.clearScreen();
	u.logo();

	cout << "\n  Do you want to save changes? (Y to confirm): ";
	u.setColor(14); cin >> saveChanges; u.setColor(15);

	if (saveChanges == "y" || saveChanges == "Y") {
		Corporation::instance()->saveUsers();
	}
	else {
		u.setColor(7); cout << "  WARNING: Changes not saved!\n"; u.setColor(15);
	}

	Sleep(1500);
	u.clearScreen();
	u.logo();
	u.aboutMessage();
	Sleep(3000);
	return 0;
}