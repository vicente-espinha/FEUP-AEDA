#include "Supplier.h"

template <typename T>
Supplier<T>::Supplier(string n, unsigned int ni)
{
	name = n;
	nif = ni;
}

template <typename T>
void Supplier<T>::readFile(string fileName)
{
	ifstream x;
	x.open(fileName);
}