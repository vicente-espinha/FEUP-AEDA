#include "Supplier.h"

Supplier::Supplier(string n, unsigned int ni)
{
	name = n;
	nif = ni;
}

void Supplier::readFile(string fileName)
{
	ifstream x;
	x.open(fileName);
}