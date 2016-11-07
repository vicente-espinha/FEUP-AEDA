#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h> 
#include <conio.h>

#include "Clients.h"
#include "Supplier.h"

using namespace std;

class Menu {

	//Variables
	fstream f;

	string usersFile, suppliersFile;

	vector<Users> usersVec;
	//vector<Supplier> suppliersVec;

	string username, password;
	unsigned int nif, points;

	//Menu functionalities
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD CursorPosition;

public:
	// Option Names //
	string * Menu1Items(); // A function that returns the name of a menu item.
	string * RegisterItems();
	string * LoginItems();

	// Menu functionalities //
	void gotoxy(int, int); /* With this function you can goto any position on the cmd line screen */
	void ChangeCursorStatus(bool);

	// Menus //
	void LoginMenu();
	void RegisterMenu();
	void Menu1();

	//
	bool foundUsersFile(string userFiles);
	void loadUsers();
	void saveUsers();
	void addUser();
};