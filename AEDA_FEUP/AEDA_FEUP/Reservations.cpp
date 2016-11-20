#include "Reservations.h"

Reservation::Reservation(long nif, double price, Date d1, Date d2)
{
	this->nif = nif;
	this->price = price;
	this->d1 = d1;
	this->d2 = d2;
}
