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
	string name, address;
	unsigned int nif;
	vector<Rent> v;
public:
	Supplier(string n, string ad, unsigned int ni);
	string getName() { return name; }
	string getAddress() { return address; }
	unsigned int getNif() { return nif; }
	vector<Rent> getVector() { return v; }
	void setVector(vector<Rent> v2) { v = v2; }
};