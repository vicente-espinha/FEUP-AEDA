#pragma once



#include <iostream>
#include <string>

using namespace std;

/*! \brief Brief description.
*
*  Class dedicated to the configuration and to a easier access of a date .
*/
class Date
{
private:
	int day, month, year;/*!< "day" is the day of a date,"month" is the month of a date and "year" is the year of the date */
public:
	Date();
	Date(string line);
	Date(int, int, int);
<<<<<<< HEAD
	void setDay(int);
	int getDay();
	void setMonth(int);
	int getMonth();
	void setYear(int);
	int getYear();
	bool isValid();
	friend bool operator<(const Date &D1, Date &D2);
	friend bool operator>(const Date &D1, Date &D2);
	friend bool operator==(const Date &d1, Date &d2);
	Date operator+(Date days);    // Retorna o resultado das datas
	Date operator-(Date days);    
	int minus(Date days);     // Retorna a diferenca das datas, para fins de price e whatnot
	friend ostream& operator<<(ostream& out, const Date & data);
=======
	void setDay(int);//!< a function that sets the day.
	int getDay();//!< a function that returns the day.
	void setMonth(int);//!< a function that sets the month.
	int getMonth();//!< a function that returns the month.
	void setYear(int);//!< a function that sets the year.
	int getYear();//!< a function that returns the year.
	bool isValid();//!< a function that returns true if the date is valid,if not returns false.
	friend bool operator<(const Date & D1,Date &D2);//!< a function that overloads the operator "<".
	friend bool operator>(const Date & D1, Date &D2);//!< a function that overloads the operator ">".
	friend bool operator==(const Date &d1, Date &d2);//!< a function that overloads the operator "==".
	Date operator+(Date days);//!< a function that returns the result of the sum of the dates.
	Date operator-(Date days);//!< a function that returns the result of the subtraction of the dates.
	int minus(Date days);//!< a function that returns the diference of the days between dates.
	friend ostream& operator<<(ostream& out, const Date & data);//!< a function that overloads the operator "<<".
>>>>>>> origin/master
};
