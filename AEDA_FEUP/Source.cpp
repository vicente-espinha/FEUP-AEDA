#include "Corporation.h"
#include "Menu.h"


Corporation* Corporation::singleton_instance = 0;

int main() {

	string usersFile, suppliersFile, rentsFile;

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
	cout << "\n  Rents file:       ";
	u.setColor(14); getline(cin, rentsFile); u.setColor(15);

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

	if (!(Corporation::instance()->foundRentsFile(rentsFile))) {
		return 0;
	}

	Corporation::instance()->loadUsers();
	Corporation::instance()->loadSuppliers();
	Corporation::instance()->loadRents();
	Corporation::instance()->orderRentsVec();
	Corporation::instance()->createPriorityQueueFromRents();
	Corporation::instance()->createBST();

	u.clearScreen();
	
	menu.MainMenu();

	u.clearScreen();
	u.logo();

	
	return 0;
}