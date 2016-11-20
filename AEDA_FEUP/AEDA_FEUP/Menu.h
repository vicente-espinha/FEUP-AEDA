#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h> 
#include <conio.h>

#include "Utilities.h"
#include "Corporation.h"

using namespace std;

class Menu {
	//Menu functionalities
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD CursorPosition;

public:
	// Option Names //
	string * UsersMenuItems(); // A function that returns the name of a menu item.
	string * RegisterItems();
	string * MainMenuItems();
	string * SuppliersMenuItems();

	// Menu functionalities //
	void gotoxy(int, int); /* With this function you can goto any position on the cmd line screen */
	void ChangeCursorStatus(bool);

	// Menus //
	int MainMenu();
	int RegisterMenu();
	int UsersMenu();
	int SuppliersMenu();
};