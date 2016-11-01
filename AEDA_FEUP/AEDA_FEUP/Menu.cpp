#include <iostream>
#include <string>
#include <windows.h> 
#include <conio.h>
#include "Menu.h"
#include "Utilities.h"
#include <vector>
#include "Rent.h"

using namespace std;

Menu m;
Utilities u;

bool file_verify(string file)
{
	fstream c(file);
	if (c.fail())
	{
		c.close();
		return false;
	}
		c.close();
		return true;
}

/*vector<Rent>rents(string file)   //not finished
{
	ifstream c(file);
	vector<Rent>pro;
	string name, type, type_type, price, day1, day2, mouth1, mouth2, year1, year2;
	getline(c, name, ';');
	getline(c, type, ';');
	getline(c, type_type, ';');
	getline(c, price, ';');
	getline(c, day1, ';');
	getline(c, day2, ';');
	getline(c, mouth1, ';');
	getline(c, mouth2, ';');
	getline(c, year1, ';');
	getline(c, year2, ';');
	Date d1, d2;
	d1;

	c.close();
	return pro;
}*/

vector<Clients>clients(string file)
{
	ifstream c(file);
	vector<Clients>pro;
	while (!c.eof())
	{
		string username, password, pontos, NIF;
		getline(c, username, ';');
		getline(c, password, ';');
		getline(c, NIF, ';');
		getline(c, pontos, ';');
		Clients x=Clients(username,password,atoi(NIF.c_str()),atoi(pontos.c_str()));
		pro.push_back(x);
	}
	c.close();
	return pro;
}

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
string * Menu::LoginItems() {

	string *item = new string[3];
	item[0] = "Login";
	item[1] = "Register";
	item[2] = "Continue as unregistered user";

	return item;
}
//-----------------------------------------------
string * Menu::RegisterItems() {

	string *item = new string[2];
	item[0] = "Register as a suplier";
	item[1] = "Register as a basic white user";

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

/*-------Login Menu options--------*/
void LoginOption() {

	u.clearScreen();
	m.gotoxy(25, 10);
	cout << "You have selected menu option (#1)" << endl;
	u.pressToContinueMessage();
	u.clearScreen();

}

void RegisterOption() {

	u.clearScreen();
	m.RegisterMenu();
	u.clearScreen();

}

void UnregUserOption() {

	u.clearScreen();
	m.Menu1();
	u.clearScreen();

}

/*-------Register Menu Options------*/
void SuplierOption() {

	u.clearScreen();
	cout << "Name: \n" << endl;
	cout << "Password: \n" << endl;

}

void UserOption() {

	u.clearScreen();
	cout << "Name: \n" << endl;
	cout << "Password: \n" << endl;
	

}

/*-------Menu 1 options--------*/
void Option1() {

	u.clearScreen();
	m.gotoxy(25, 10);
	cout << "You have selected menu option (#1)" << endl;
	u.pressToContinueMessage();
	u.clearScreen();
}

void Option2() {

	u.clearScreen();
	m.gotoxy(25, 10);
	cout << "You have selected menu option (#2)" << endl;
	u.pressToContinueMessage();
	u.clearScreen();
}

void Option3() {

	u.clearScreen();
	m.gotoxy(25, 10);
	cout << "You have selected menu option (#3)" << endl;
	u.pressToContinueMessage();
	u.clearScreen();
}

void ExitOption() {

	m.gotoxy(30, 15);
	cout << "Exitting..." << endl;
	u.pressToContinueMessage();
	exit(0);
}

/*--------------------------------------------------Menu Initialization-------------------------------------------------*/
void Menu::LoginMenu() {

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
			cout << LoginItems()[i] << endl;
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

void Menu::RegisterMenu() {

	ChangeCursorStatus(false);
	typedef void(*TMenuOption)();

	int ItemCount = 2; // This variable holds the number of menu items.
	int MenuChoice = 1; // This variable holds the position of the cursor. 
	char key; //For entering the key (up arrow,down arrow,etc...).

	TMenuOption *MenuOption = new TMenuOption[ItemCount]; //Array of pointers to functions (dynamic).
	MenuOption[0] = SuplierOption; //Filling the array with the functions.
	MenuOption[1] = UserOption;

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
