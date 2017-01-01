#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h> 
#include <conio.h>

#include "Utilities.h"


using namespace std;

/*! \brief Brief description.
*
* Classe that is a menu
*/
class Menu {
	//Menu functionalities
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD CursorPosition;

public:
	// Option Names //
	string * UsersMenuItems(); //!< a function that returns the user menu items
	string * RegisterItems();//!< a function that returns the register Itmes
	string * MainMenuItems();//!< a function that returns the main menu items
	string * SuppliersMenuItems();//!< a function that returns the suppliers menu items
	string * ManagmentItems();

	// Menu functionalities //
	void gotoxy(int, int); //!< a function that gets you to a position in the cmd line screen
	void ChangeCursorStatus(bool);//!< a function that changes the position of the cursor

	// Menus //
	int MainMenu();//!< a function that returns the  main menu
	int RegisterMenu();//!< a function that returns the register menu
	int UsersMenu();//!< a function that returns the  users menu
	int SuppliersMenu();//!< a function that returns the suppliers menu
	int ManagmentMenu();
};