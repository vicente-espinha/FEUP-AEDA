#include "Supplier.h"

Supplier::Supplier(){}

Supplier::Supplier(string n, string password, long ni, string ad)
{
	name = n;
	this->password = password;
	address = ad;
	nif = ni;

}

