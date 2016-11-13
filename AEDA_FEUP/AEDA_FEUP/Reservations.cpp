#include "Reservations.h"

Reservation::Reservation(string name, string type, string type_type, int n, Date d1, Date d2,Rent * rent)
{
	this->name = name;
	this->type_rent = type;
	this->type_type_rent = type_type;
	this->total_price = d2.minus(d1) * rent->getPrice();
	this->d1 = d1;
	this->d2 = d2;
	this->n_people=n;
	this->rent = rent;
}

bool operator==(const Reservation & R1, const Reservation & R2)
{
	if (R1.name == R2.name && R1.type_rent == R2.type_rent && R1.type_type_rent == R2.type_type_rent && R1.total_price == R2.total_price && R1.d1 == R2.d1 && R1.d2 == R2.d2 && R1.n_people == R2.n_people && R1.rent == R2.rent)
		return true;
	else
		return false;
}