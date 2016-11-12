#include "Supplier.h"

/*
template <typename T>
void Supplier<T>::readFile(string fileName)
{
	ifstream x;
	x.open(fileName);
}*/

Supplier::Supplier(string n, string ad, unsigned int ni, vector<Rent> v2)
{
	name = n;
	address = ad;
	nif = ni;
	v = v2;
//	v = buildRent();
}

/*
string name, address;
unsigned int nif;
vector<Rent<T>> v;
*/