#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

#include "Corporation.h"


Corporation* Corporation::singleton_instance = 0;

int main() {

	string usersFile, suppliersFile;

	//Objetos da classe. 
	Menu menu;
	Utilities u;

	u.setColor(15); u.logo();
	cout << "\n  In order to ensure the software runs as expected, an initial setup is necessary.\n"; Sleep(1);
	cout << "\n  You will be now asked to input the name of the resource files. \n"; Sleep(1);

	//CLIENTS FILE TEST (FOUND/VALID)
	cout << "\n  Users file:       ";
	u.setColor(14); getline(cin, usersFile); u.setColor(15);
	cout << "\n  Suppliers file:   ";
	u.setColor(14); getline(cin, suppliersFile); u.setColor(15);

	if (cin.eof()) {
		u.cancelMessage();
		return 0;
	}

	if (!(Corporation::instance()->foundUsersFile(usersFile))) {
		return 0;
	}
	
	if (!(Corporation::instance()->foundSuppliersFile(suppliersFile))) {
		return 0;
	}

	Corporation::instance()->loadUsers();
	
	Corporation::instance()->loadSuppliers();
	Sleep(4000);
	Corporation::instance()->orderSuppliersVec();
	u.clearScreen();
	//Corporation::instance()->printSuppliers();
	
	menu.MainMenu();

	u.clearScreen();
	u.logo();

	Corporation::instance()->saveUsers();
	Corporation::instance()->saveSuppliers();
	
	u.clearScreen();
	u.logo();
	u.aboutMessage();
	return 0;
}