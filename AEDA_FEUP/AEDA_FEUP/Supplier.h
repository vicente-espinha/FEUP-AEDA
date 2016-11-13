#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Rent.h"

using namespace std;


class Supplier
{
protected:
	string name, password, address;
	unsigned int nif;
	vector<Rent> v;
public:
	Supplier(string n, string password, unsigned int ni, string ad, vector<Rent> v);
	string getName() { return name; }
	string getPassword() { return password; }
	string getAddress() { return address; }
	unsigned int getNif() { return nif; }
	vector<Rent> getVector() { return v; }
};