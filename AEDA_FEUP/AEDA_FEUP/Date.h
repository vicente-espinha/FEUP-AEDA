#pragma once



#include <iostream>
#include <string>

using namespace std;

class Date
{
private:
	int day, month, year;
public:
	Date();
	Date(string line);
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
	friend bool operator==(const Date &d1, Date &d2);
	Date operator+(Date days);    // Retorna o resultado das datas
	Date operator-(Date days);    
	int minus(Date days);     // Retorna a diferenca das datas, para fins de price e whatnot
	friend ostream& operator<<(ostream& out, const Date & data);
};
