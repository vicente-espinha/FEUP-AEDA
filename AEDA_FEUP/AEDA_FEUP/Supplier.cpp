#include "Supplier.h"


template <typename T>
void Supplier<T>::readFile(string fileName)
{
	ifstream x;
	x.open(fileName);
}

template <typename T>
Supplier<T>::Supplier(string n, string ad, unsigned int ni)
{
	name = n;
	address = ad;
	nif = ni;
	v = buildRent();
}

template <typename T>
void Supplier<T>::readFile()
{
	ifstream f;

	f.open("suppliers.txt");

	/*
	while (!f.eof())
	{
		string username, password, pontos, NIF;
		getline(c, username, ';');
		getline(c, password, ';');
		getline(c, NIF, ';');
		getline(c, pontos, ';');
		Clients x = Clients(username, password, atoi(NIF.c_str()), atoi(pontos.c_str()));
		pro.push_back(x);
	}
	*/
}


/*
string name, address;
unsigned int nif;
vector<Rent<T>> v;
*/