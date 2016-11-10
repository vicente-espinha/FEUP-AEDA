#include "Reservations.h"
template<typename T>
Reservation<T>::Reservation(string name, string type, string type_type, int n, Date d1, Date d2,Rent<T> * rent)
{
	this->name = name;
	this->type_rent = type;
	this->type_type_rent = type_type;
	this->total_price = d2.minus(d1) * rent->ge ;
	this->d1 = d1;
	this->d2 = d2;
	this->n_people=n;
	this->rent = rent;
}