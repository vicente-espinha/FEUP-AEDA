#include "Supplier.h"

/*
template <typename T>
void Supplier<T>::readFile(string fileName)
{
	ifstream x;
	x.open(fileName);
}*/

Supplier::Supplier(string n, string password, unsigned int ni, string ad, vector<Rent> v)
{
	name = n;
	this->password = password;
	address = ad;
	nif = ni;
	this->v = v;
}

/*
string name, address;
unsigned int nif;
vector<Rent<T>> v;
*/