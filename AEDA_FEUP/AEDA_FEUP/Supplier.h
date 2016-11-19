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
	Supplier();
	Supplier(string n, string password, unsigned int ni, string ad, vector<Rent> v);
	string getName() { return name; }
	void setName(string s) { name = s; }
	string getPassword() { return password; }
	string getAddress() { return address; }
	void setVector(vector<Rent> v2) { v = v2; }
	unsigned int getNif() { return nif; }
	vector<Rent> getVector() { return v; }
};