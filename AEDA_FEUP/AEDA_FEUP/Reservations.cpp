#include "Reservations.h"

Reservation::Reservation(string name,string city, string type, string type_type, int n, Date d1, Date d2,Rent * rent)
{
	this->username = name;
	this->type_rent = type;
	this->type_type_rent = type_type;
	this->total_price = d2.minus(d1) * rent->getPrice();
	this->d1 = d1;
	this->d2 = d2;
	this->n_people=n;
	this->rent = rent;
	this->city = city;
}