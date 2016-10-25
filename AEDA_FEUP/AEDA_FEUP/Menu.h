#pragma once
#include <iostream>
#include <string>
#include <windows.h> 
#include <conio.h> 

using namespace std;

class Menu {

	//Menu functionalities
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD CursorPosition;

public:
	// Option Names //
	string * Menu1Items(); // A function that returns the name of a menu item.
	string * RegisterItems();

	//Menu functionalities
	void gotoxy(int, int); // With this function you can goto any position on the cmd line screen.
	void ChangeCursorStatus(bool);

	//Menus
	void RegisterMenu();
	void Menu1();
};