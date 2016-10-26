#pragma once



#include <iostream>
#include <string>
#include <fstream>

class Data
{
private:
	int day, month, year;
public:
	Data();
	Data(int, int, int);
	void setDay(int);
	int getDay();
	void setMonth(int);
	int getMonth();
	void setYear(int);
	int getYear();
	bool isValid(int day, int month, int year);
	bool isBetween(Data begin, Data end, Data timeGiven);
};
