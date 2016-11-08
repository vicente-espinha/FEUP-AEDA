#include <iostream>
#include <string>
#include <windows.h> 
#include <conio.h>
#include <vector>

#include "Menu.h"
#include "Utilities.h"
#include "Rent.h"
#include "Clients.h"

using namespace std;

bool isRunning = true;

//Class objects
Menu m;
Utilities u;

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


string * Menu::LoginItems() {

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
string * Menu::Menu1Items() {

	string *item = new string[5];
	item[0] = "Menu Option #1.";
	item[1] = "Menu Option #2.";
	item[2] = "Menu Option #3.";
	item[3] = "Return to Main Menu";
	item[4] = "Exit.";

	return item;
}


///////////////////
// MENU OPTIONS //
//////////////////


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
void SupplierOption() {

	u.clearScreen();
	cout << "Name: \n" << endl;
	cout << "Password: \n" << endl;
}

void UserOption() {

	u.clearScreen();
	u.setColor(14); cout << "\n  ::| REGISTER |::\n"; u.setColor(15);
	m.registerUser();
	m.Menu1();

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

/*-------Return and exit options--------*/
void returnMain() {

	u.clearScreen();
	m.LoginMenu();
}

void ExitOption() {

	isRunning = false;

}


//////////////////////////
// MENU INITIALIZATION //
/////////////////////////


int Menu::LoginMenu() {

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

		for (int i = 0; i < ItemCount; i++) { // Draw the menu.

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
	MenuOption[2] = returnMain;
	MenuOption[3] = ExitOption;

	while (1) {

		for (int i = 0; i < ItemCount; i++) { // Draw the menu.

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

int Menu::Menu1() {

	ChangeCursorStatus(false);
	typedef void(*TMenuOption)();

	int ItemCount = 5; // This variable holds the number of menu items.
	int MenuChoice = 1; // This variable holds the position of the cursor. 
	char key; //For entering the key (up arrow,down arrow,etc...).

	TMenuOption *MenuOption = new TMenuOption[ItemCount]; //Array of pointers to functions (dynamic).
	MenuOption[0] = Option1; //Filling the array with the functions.
	MenuOption[1] = Option2;
	MenuOption[2] = Option3;
	MenuOption[3] = returnMain;
	MenuOption[4] = ExitOption;

	while (1) {

		for (int i = 0; i < ItemCount; i++) { // Draw the menu.

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


//////////////////////
// USERS FUNCTIONS //
/////////////////////


//Checks existance of the users file
bool Menu::foundUsersFile(string usersFile) {

	f.open(usersFile);

	if (f.fail()) {
		f.close();
		u.setColor(12); cerr << "\n  ERROR: " << usersFile << " (users file) could not be found!\n         Verify the directory!\n\n"; u.setColor(15);
		return false;
	}

	f.close();

	this->usersFile = usersFile;
	return true;
}

//Loads the users file to memory (Users vector)
void Menu::loadUsers() {

	string line;

	f.open(usersFile);
	getline(f, line);

	while (getline(f, line)) {

		string username = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		string password = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		unsigned int nif = stoi(line.substr(0, line.find(" ; ")));
		line.erase(0, line.find(" ; ") + 3);
		unsigned int points = stoi(line.substr(0, line.length()));

		usersVec.push_back(Users(username, password, nif, points));
	}
	f.close();
	return;
}

//Loads memory to the users file
void Menu::saveUsers() {

	ofstream p("tempSave.txt");

	for (size_t i = 0; i < usersVec.size(); i++) {
		p << usersVec[i].getUsername() << " ; " << usersVec[i].getPassword() << " ; " << usersVec[i].getNif() << " ; " << usersVec[i].getPoints() << endl;
	}

	p.close();
	remove(usersFile.c_str());
	rename("tempSave.txt", usersFile.c_str());
	return;
}

//Adds a user to the users vector
void Menu::registerUser() {

	cout << "\n Name:  "; getline(cin, username);

	if (cin.eof()) {
		u.cancelMessage();
		return;
	}

	for (unsigned int index = 0; index != username.size(); index++) {
		if (!isalpha(username[index]) && username[index] != ' ') {
			u.setColor(12); cerr << "  ERROR: Name must only contain alphabetic characters. "; u.setColor(15);
			Sleep(3000);
			u.clearScreen();
			return;
		}
	}

	cout << "\n Password:  "; cin >> password;
	u.cinClear();
	cout << "\n NIF:  "; cin >> nif;

	u.cinClear();

	if (cin.eof()) {
		u.cancelMessage();
		return;
	}

	usersVec.push_back(Users(username, password, nif, 0));

	for (size_t i = 0; i < usersVec.size(); i++) {
		cout << usersVec[i].getUsername() << " ; " << usersVec[i].getPassword() << " ; " << usersVec[i].getNif() << " ; " << usersVec[i].getPoints() << endl;
	}

	u.successMessage();
	return;
}
