#include "Data.h"

Data::Data()
{
	day = 0;
	month = 0;
	year = 0;
}

Data::Data(int day, int month, int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}

void Data::setDay(int day)
{
	this->day = day;
}

int Data::getDay()
{
	return day;
}

void Data::setMonth(int month)
{
	this->month = month;
}

int Data::getMonth()
{
	return month;
}

void Data::setYear(int year)
{
	this->year = year;
}

int Data::getYear()
{
	return year;
}

bool Data::isValid(int day, int month, int year)
{

	if (month < 1 || month > 12)
	{
		return false;
	}
	if (year < 1969 || year > 2016)
	{
		return false;
	}
	if (month == 1 || month == 5 || month == 7 || month == 10 || month == 3 || month == 12 || month == 8)
	{
		if (day < 1 || day > 31)
		{
			return false;
		}
	}
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day < 1 || day > 30)
		{
			return false;
		}
	}
	if (month == 2 && (day < 1 || day > 28))
		return false;
	return true;
}

bool Data::isBetween(Data begin, Data end, Data timeGiven)
{
	if (begin.getYear() < timeGiven.getYear())
	return false;
}


