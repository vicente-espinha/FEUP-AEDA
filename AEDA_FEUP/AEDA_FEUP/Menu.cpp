#include <iostream>
#include <string>
#include <windows.h> 
#include <conio.h>
#include <vector>

#include "Menu.h"

using namespace std;

bool isRunning = true;

//Class objects
Menu m;
Utilities u;

///////////////////////////
// MENU FUNCTIONALITIES //
//////////////////////////


void Menu::gotoxy(int xpos, int ypos) {

	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}
//---------------------------------------------
void Menu::ChangeCursorStatus(bool Visible) {

	CONSOLE_CURSOR_INFO *c = new CONSOLE_CURSOR_INFO;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (Visible) {

		c->bVisible = TRUE;
		c->dwSize = 0;//(0) is invild so the default value is set
	}
	else {

		c->bVisible = FALSE;
		c->dwSize = 1;//it must be assigned to a valid value
	}

	SetConsoleCursorInfo(h, c);
}


///////////////////
// OPTION NAMES //       /*Loads the arrays with the different menu functions*/
//////////////////


string * Menu::MainMenuItems() {

	string *item = new string[4];
	item[0] = "Login";
	item[1] = "Register";
	item[2] = "Continue as unregistered user";
	item[3] = "Exit";

	return item;
}
//-----------------------------------------------
string * Menu::RegisterItems() {

	string *item = new string[4];
	item[0] = "Register as a supplier";
	item[1] = "Register as a user";
	item[2] = "Return to Main Menu";
	item[3] = "Exit";

	return item;
}
//----------------------------------------------
string * Menu::UsersMenuItems() {

	string *item = new string[5];
	item[0] = "Make Reservation";
	item[1] = "Cancel Reservation";
	item[2] = "Explore";
	item[3] = "Logout";
	item[4] = "Exit";

	return item;
}
//----------------------------------------------
string * Menu::SuppliersMenuItems() {

	string *item = new string[5];
	item[0] = "Create Rent";
	item[1] = "Delete Rent";
	item[2] = "Your rents";
	item[3] = "Logout";
	item[4] = "Exit";

	return item;
}

///////////////////
// MENU OPTIONS //
//////////////////


/*-------Main Menu options--------*/
void LoginOption() {

	u.clearScreen();
	Corporation::instance()->login();
	u.clearScreen();

}

void RegisterOption() {

	u.clearScreen();
	m.RegisterMenu();
	u.clearScreen();

}

void UnregUserOption() {

	u.clearScreen();
	m.UsersMenu();
	u.clearScreen();

}

/*-------Register Menu Options------*/
void SupplierOption() {

	u.clearScreen();
	u.setColor(14); cout << "\n  ::| REGISTER |::\n"; u.setColor(15);
	Corporation::instance()->registerSupplier();
	m.MainMenu();
}

void UserOption() {

	u.clearScreen();
	u.setColor(14); cout << "\n  ::| REGISTER |::\n"; u.setColor(15);
	Corporation::instance()->registerUser();
	m.MainMenu();

}

/*-------Users Menu options--------*/
void MakeReservationOption() {

	u.clearScreen();
	m.gotoxy(25, 10);
	cout << "You have selected menu option (#1)" << endl;
	u.pressToContinueMessage();
	u.clearScreen();
}

void CancelReservationOption() {

	u.clearScreen();
	m.gotoxy(25, 10);
	cout << "You have selected menu option (#2)" << endl;
	u.pressToContinueMessage();
	u.clearScreen();
}

void ExploreOption() {

	u.clearScreen();
	m.gotoxy(25, 10);
	cout << "You have selected menu option (#3)" << endl;
	u.pressToContinueMessage();
	u.clearScreen();
}

/*-------Suppliers Menu options--------*/
void CreateRentOption() {

	u.clearScreen();
	m.gotoxy(25, 10);
	cout << "You have selected menu option (#1)" << endl;
	u.pressToContinueMessage();
	u.clearScreen();
}

void DeleteRentOption() {

	u.clearScreen();
	m.gotoxy(25, 10);
	cout << "You have selected menu option (#2)" << endl;
	u.pressToContinueMessage();
	u.clearScreen();
}

void ViewAllRentsOption() {

	u.clearScreen();
	m.gotoxy(25, 10);
	cout << "You have selected menu option (#3)" << endl;
	u.pressToContinueMessage();
	u.clearScreen();
}

/*-------Return and exit options--------*/
void Logout() { u.clearScreen(); m.MainMenu(); }

void ExitOption() { isRunning = false; }


//////////////////////////
// MENU INITIALIZATION //
/////////////////////////


int Menu::MainMenu() {

	ChangeCursorStatus(false);
	typedef void(*TMenuOption)();

	int ItemCount = 4; // This variable holds the number of menu items.
	int MenuChoice = 1; // This variable holds the position of the cursor. 
	char key; //For entering the key (up arrow,down arrow,etc...).

	TMenuOption *MenuOption = new TMenuOption[ItemCount]; //Array of pointers to functions (dynamic).
	MenuOption[0] = LoginOption; //Filling the array with the functions.
	MenuOption[1] = RegisterOption;
	MenuOption[2] = UnregUserOption;
	MenuOption[3] = ExitOption;

	while (1) {

		for (int i = 0; i < ItemCount; i++) { // Draw the m.

			gotoxy(2, 2 + i);
			MenuChoice == i + 1 ? cout << " -> " : cout << "    "; // if (i+1) == MenuChoice, ' -> ', else print '    '.
			cout << MainMenuItems()[i] << endl;
		}

		key = _getch(); //get the key.

		switch (key) {

		case '\r': // if the entered key is 'Enter'.
			try {

				(*MenuOption[MenuChoice - 1])();
			}
			catch (...) {}

			if (!isRunning) {
				return 0;
			}

			break;

		case 'P': // if the entered key is the 'up arrow'
			MenuChoice++;
			if (MenuChoice > ItemCount)
				MenuChoice = 1;
			break;

		case 'H': //If the entered key is the 'down arrow'
			MenuChoice--;
			if (MenuChoice < 1)
				MenuChoice = ItemCount;
			break;

		case 27: // If the entered key is the escape key (Esc)
			try { (*MenuOption[ItemCount - 1])(); }
			catch (...) {}
			break;
		default:// any another key.
			if (key >= '1' && key <= char(ItemCount + '0')) {

				try { (*MenuOption[int(key) - '0' - 1])(); }

				catch (...) {}
			}
		}
	}

	delete MenuOption;
	return 0;
}

int Menu::RegisterMenu() {

	if (!isRunning) {
		return 0;
	}

	ChangeCursorStatus(false);
	typedef void(*TMenuOption)();

	int ItemCount = 4; // This variable holds the number of menu items.
	int MenuChoice = 1; // This variable holds the position of the cursor. 
	char key; //For entering the key (up arrow,down arrow,etc...).

	TMenuOption *MenuOption = new TMenuOption[ItemCount]; //Array of pointers to functions (dynamic).
	MenuOption[0] = SupplierOption; //Filling the array with the functions.
	MenuOption[1] = UserOption;
	MenuOption[2] = Logout;
	MenuOption[3] = ExitOption;

	while (1) {

		for (int i = 0; i < ItemCount; i++) { // Draw the m.

			gotoxy(2, 2 + i);
			MenuChoice == i + 1 ? cout << " -> " : cout << "    "; // if (i+1) == MenuChoice, ' -> ', else print '    '.
			cout << RegisterItems()[i] << endl;
		}

		key = _getch(); //get the key.

		switch (key) {

		case '\r': // if the entered key is 'Enter'.
			try {

				(*MenuOption[MenuChoice - 1])();
			}
			catch (...) {}

			if (!isRunning) {
				return 0;
			}

			break;

		case 'P': // if the entered key is the 'up arrow'
			MenuChoice++;
			if (MenuChoice > ItemCount)
				MenuChoice = 1;
			break;

		case 'H': //If the entered key is the 'down arrow'
			MenuChoice--;
			if (MenuChoice < 1)
				MenuChoice = ItemCount;
			break;

		case 27: // If the entered key is the escape key (Esc)
			try { (*MenuOption[ItemCount - 1])(); }
			catch (...) {}
			break;
		default:// any another key.
			if (key >= '1' && key <= char(ItemCount + '0')) {

				try { (*MenuOption[int(key) - '0' - 1])(); }

				catch (...) {}
			}
		}
	}

	delete MenuOption;
	return 0;

}

int Menu::UsersMenu() {

	ChangeCursorStatus(false);
	typedef void(*TMenuOption)();

	int ItemCount = 5; // This variable holds the number of menu items.
	int MenuChoice = 1; // This variable holds the position of the cursor. 
	char key; //For entering the key (up arrow,down arrow,etc...).

	TMenuOption *MenuOption = new TMenuOption[ItemCount]; //Array of pointers to functions (dynamic).
	MenuOption[0] = MakeReservationOption; //Filling the array with the functions.
	MenuOption[1] = CancelReservationOption;
	MenuOption[2] = ExploreOption;
	MenuOption[3] = Logout;
	MenuOption[4] = ExitOption;

	while (1) {

		for (int i = 0; i < ItemCount; i++) { // Draw the m.

			gotoxy(2, 2 + i);
			MenuChoice == i + 1 ? cout << " -> " : cout << "    "; // if (i+1) == MenuChoice, ' -> ', else print '    '.
			cout << UsersMenuItems()[i] << endl;
		}

		key = _getch(); //get the key.

		switch (key) {

		case '\r': // if the entered key is 'Enter'.
			try {

				(*MenuOption[MenuChoice - 1])();
			}
			catch (...) {}

			if (!isRunning) {
				return 0;
			}

			break;

		case 'P': // if the entered key is the 'up arrow'
			MenuChoice++;
			if (MenuChoice > ItemCount)
				MenuChoice = 1;
			break;

		case 'H': //If the entered key is the 'down arrow'
			MenuChoice--;
			if (MenuChoice < 1)
				MenuChoice = ItemCount;
			break;

		case 27: // If the entered key is the escape key (Esc)
			try { (*MenuOption[ItemCount - 1])(); }
			catch (...) {}
			break;
		default:// any another key.
			if (key >= '1' && key <= char(ItemCount + '0')) {

				try { (*MenuOption[int(key) - '0' - 1])(); }

				catch (...) {}
			}
		}
	}

	delete MenuOption;
	return 0;
}

int Menu::SuppliersMenu() {

	ChangeCursorStatus(false);
	typedef void(*TMenuOption)();

	int ItemCount = 5; // This variable holds the number of menu items.
	int MenuChoice = 1; // This variable holds the position of the cursor. 
	char key; //For entering the key (up arrow,down arrow,etc...).

	TMenuOption *MenuOption = new TMenuOption[ItemCount]; //Array of pointers to functions (dynamic).
	MenuOption[0] = CreateRentOption; //Filling the array with the functions.
	MenuOption[1] = DeleteRentOption;
	MenuOption[2] = ViewAllRentsOption;
	MenuOption[3] = Logout;
	MenuOption[4] = ExitOption;

	while (1) {

		for (int i = 0; i < ItemCount; i++) { // Draw the m.

			gotoxy(2, 2 + i);
			MenuChoice == i + 1 ? cout << " -> " : cout << "    "; // if (i+1) == MenuChoice, ' -> ', else print '    '.
			cout << SuppliersMenuItems()[i] << endl;
		}

		key = _getch(); //get the key.

		switch (key) {

		case '\r': // if the entered key is 'Enter'.
			try {

				(*MenuOption[MenuChoice - 1])();
			}
			catch (...) {}

			if (!isRunning) {
				return 0;
			}

			break;

		case 'P': // if the entered key is the 'up arrow'
			MenuChoice++;
			if (MenuChoice > ItemCount)
				MenuChoice = 1;
			break;

		case 'H': //If the entered key is the 'down arrow'
			MenuChoice--;
			if (MenuChoice < 1)
				MenuChoice = ItemCount;
			break;

		case 27: // If the entered key is the escape key (Esc)
			try { (*MenuOption[ItemCount - 1])(); }
			catch (...) {}
			break;
		default:// any another key.
			if (key >= '1' && key <= char(ItemCount + '0')) {

				try { (*MenuOption[int(key) - '0' - 1])(); }

				catch (...) {}
			}
		}
	}

	delete MenuOption;
	return 0;

}
