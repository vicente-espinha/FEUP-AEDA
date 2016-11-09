#include "Reservations.h"
template<typename T>
Reservation::Reservation(string name, string type, string type_type, int n,double price, Date d1, Date d2,Rent<T> * rent)
{
	this->name = name;
	this->type_rent = type;
	this->type_type_rent = type_type;
	this->total_price = price;
	this->d1 = d1;
	this->d2 = d2;
	this->n_people=n;
	this->rent = rent;
}