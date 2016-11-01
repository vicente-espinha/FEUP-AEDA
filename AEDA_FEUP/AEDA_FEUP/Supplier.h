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
	Supplier(string n, unsigned int ni);
	void readFile(string fileName);
	void writeVector(Rent r) { this->v.push_back(r); }
	string getName() { return name; }
	string getAddress() { return address; }

};