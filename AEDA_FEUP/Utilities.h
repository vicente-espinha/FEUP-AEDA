#pragma once
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <string>

using namespace std;
/*! \brief Brief description.
*
*  Class dedicated to some functions that will be used many times
*/
class Utilities {

public:
	Utilities();
	void clearScreen();//!< a function that "clears" the console
	void setColor(int x);//!< a function that changes the output colors of the console
	void cinClear();//!< a function that clears the cin buffer.
	void cancelMessage();//!< a function that prints a message saying tht the opration was canceled.
	void successMessage();//!< a function that prints a message saying that the operations was a success
	void pressToContinueMessage();//!< a function that prints a message that says to press enter to continue.
	void aboutMessage();//!< a function that prints a message saying who developed the program.
	void logo();//!< a function that prints the logo.
	bool invalidInputRetry();//!< a function that prints a message syaing that the input was incorrect and that lets you try again.
	bool invalidInputNoRetry();//!< a function that prints a message syaing that the input was incorrect and that does not let you try again.
	string trim(string s);//!< a function that returns a string trimmed
};