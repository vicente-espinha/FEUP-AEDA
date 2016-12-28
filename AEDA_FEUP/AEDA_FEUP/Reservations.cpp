#include "Reservations.h"

Reservation::Reservation(long nif, double price, Date d1, Date d2)
{
	this->nif = nif;
	this->price = price;
	this->d1 = d1;
	this->d2 = d2;
}

/*Reservation::Reservation(string name, long nif, double price, Date d1, Date d2, Date reservationDate)
{
	this->name = name;
	this->nif = nif;
	this->price = price;
	this->d1 = d1;
	this->d2 = d2;
	this->reservationDate = reservationDate;
	
}*/

/*bool Reservation::operator<(const Reservation & r) const {

	if (this->name == r.getName() || (r.getName() == "" && this->nif == r.getnif())) {

		return this->reservationDate < r.getReservationDate();

	} else if (r.getName() == "") {

		return this->nif < r.getnif();

	}
	else {

		return this->name < r.getName();
	}
}*/