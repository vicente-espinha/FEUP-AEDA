#include <iostream>
#include <vector>
#include "Rent.h"
#include "Clients.h"

class Company
{
protected:
	// vector<Supllier> suppliers;
	vector<Clients>clients(string file)
	{
		ifstream c(file);
		vector<Clients>pro;
		while (!c.eof())
		{
			string username, password, pontos, NIF;
			getline(c, username, ';');
			getline(c, password, ';');
			getline(c, NIF, ';');
			getline(c, pontos, ';');
			Clients x = Clients(username, password, atoi(NIF.c_str()), atoi(pontos.c_str()));
			pro.push_back(x);
		}
		c.close();
		return pro;
	}

};