#include <iostream>
#include <string>
#include <windows.h> 
#include <conio.h>
#include "Menu.h"
#include "Utilities.h"

using namespace std;

Menu m;
Utilities d;

/* ----------------------------------- Menu Functionalities ---------------------------- */
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


/* ----------------------------------------- Option Names ------------------------------ */ 
string * Menu::RegisterItems() {

	string *item = new string[3];
	item[0] = "Login";
	item[1] = "Register";
	item[2] = "Continue as unregistered user";

	return item;
}
//----------------------------------------------
string * Menu::Menu1Items() {

	string *item = new string[4];
	item[0] = "Menu Option #1.";
	item[1] = "Menu Option #2.";
	item[2] = "Menu Option #3.";
	item[3] = "Exit.";

	return item;
}

/* --------------------------------------- Menu Options ------------------------------- */

/*-------Register options--------*/
void LoginOption() {

	u.clearScreen();
	m.gotoxy(25, 10);
	cout << "You have selected menu option (#1)" << endl;
	u.pressToContinueMessage();
	system("cls");

}

void RegisterOption() {

	u.clearScreen();
	m.gotoxy(25, 10);
	cout << "You have selected menu option (#2)" << endl;
	u.pressToContinueMessage();
	system("cls");

}


void UnregUserOption() {

	u.clearScreen();
	m.Menu1();
	system("cls");

}

/*-------Menu 1 options--------*/
void Option1() {

	u.clearScreen();
	m.gotoxy(25, 10);
	cout << "You have selected menu option (#1)" << endl;
	u.pressToContinueMessage();
	system("cls");
}

void Option2() {

	u.clearScreen();
	m.gotoxy(25, 10);
	cout << "You have selected menu option (#2)" << endl;
	u.pressToContinueMessage();
	system("cls");
}

void Option3() {

	u.clearScreen();
	m.gotoxy(25, 10);
	cout << "You have selected menu option (#3)" << endl;
	u.pressToContinueMessage();
	system("cls");
}

void ExitOption() {

	m.gotoxy(30, 15);
	cout << "Exitting..." << endl;
	u.pressToContinueMessage();
	exit(0);
}


void Menu::RegisterMenu() {

	ChangeCursorStatus(false);
	typedef void(*TMenuOption)();

	int ItemCount = 3; // This variable holds the number of menu items.
	int MenuChoice = 1; // This variable holds the position of the cursor. 
	char key; //For entering the key (up arrow,down arrow,etc...).

	TMenuOption *MenuOption = new TMenuOption[ItemCount]; //Array of pointers to functions (dynamic).
	MenuOption[0] = LoginOption; //Filling the array with the functions.
	MenuOption[1] = RegisterOption;
	MenuOption[2] = UnregUserOption;

	while (1) {

		for (int i = 0; i<ItemCount; i++) { // Draw the menu.

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
			break;

		case 'P': // if the entered key is the 'up arrow'
			MenuChoice++;
			if (MenuChoice>ItemCount)
				MenuChoice = 1;
			break;

		case 'H': //If the entered key is the 'down arrow'
			MenuChoice--;
			if (MenuChoice<1)
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
	return;

}

void Menu::Menu1() {

	ChangeCursorStatus(false);
	typedef void(*TMenuOption)();

	int ItemCount = 4; // This variable holds the number of menu items.
	int MenuChoice = 1; // This variable holds the position of the cursor. 
	char key; //For entering the key (up arrow,down arrow,etc...).

	TMenuOption *MenuOption = new TMenuOption[ItemCount]; //Array of pointers to functions (dynamic).
	MenuOption[0] = Option1; //Filling the array with the functions.
	MenuOption[1] = Option2;
	MenuOption[2] = Option3;
	MenuOption[3] = ExitOption;

	while (1) {

		for (int i = 0; i<ItemCount; i++) { // Draw the menu.

			gotoxy(2, 2 + i);
			MenuChoice == i + 1 ? cout << " -> " : cout << "    "; // if (i+1) == MenuChoice, ' -> ', else print '    '.
			cout << Menu1Items()[i] << endl;
		}

		key = _getch(); //get the key.

		switch (key) {

		case '\r': // if the entered key is 'Enter'.
			try {

				(*MenuOption[MenuChoice - 1])();
			}
			catch (...){}  
			break;

		case 'P': // if the entered key is the 'up arrow'
			MenuChoice++; 
			if (MenuChoice>ItemCount) 
				MenuChoice = 1;
			break;

		case 'H': //If the entered key is the 'down arrow'
			MenuChoice--;
			if (MenuChoice<1)
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
	return;
}
