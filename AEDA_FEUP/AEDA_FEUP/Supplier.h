#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Rent.h"

using namespace std;

template <typename T>
class Supplier
{
protected:
	string name, address;
	unsigned int nif;
	vector<Rent<T>> v;
public:
	Supplier(string n, unsigned int ni);
	void readFile(string fileName);
	void writeVector(Rent<T> r) { this->v.push_back(r); }
	string getName() { return name; }
	string getAddress() { return address; }
	unsigned int getNif() { return nif; }
};