#pragma once



#include <iostream>
#include <string>
#include <fstream>

class Date
{
private:
	int day, month, year;
public:
	Date();
	Date(int, int, int);
	void setDay(int);
	int getDay();
	void setMonth(int);
	int getMonth();
	void setYear(int);
	int getYear();
	bool isValid();
	bool operator<(Date time1);
	bool operator>(Date time1);
};
