#include "Supplier.h"
#include <conio.h>
#include <windows.h>
#include <cstdlib>

Supplier::Supplier(){}

Supplier::Supplier(string n, string password, long ni, string ad)
{
	name = n;
	this->password = password;
	address = ad;
	nif = ni;

}

