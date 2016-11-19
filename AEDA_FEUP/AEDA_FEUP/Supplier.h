#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Rent.h"

using namespace std;

/*! \brief Brief description.
*
*  Classe de Suppliers contains the information about the Supplier(name,password,address and nif) and a vector that contains his rents
*/
class Supplier
{
protected:
	string name, password, address;/*!< "name" is the username of the Supplier,"password" is the password of the account of the supplier and the "address" is the adrees of the Supplier*/
	unsigned int nif;/*!< "nif" is the numero de identificacao fiscal do Supplier*/
	vector<Rent> v;/*!< "v" is a vector that contains Suplier's Rents*/
	
public:	
	Supplier();
	Supplier(string n, string password, unsigned int ni, string ad, vector<Rent> v);
	string getName() { return name; }//!< a function that returns the name.
	void setName(string s) { name = s; }//!< a function that sets the name.
	string getPassword() { return password; }//!< a function that returns the password.
	string getAddress() { return address; }//!< a function that returns the address.
	void setVector(vector<Rent> v2) { v = v2; }//!< a function that sets the vector of rents.
	unsigned int getNif() { return nif; }//!< a function that returns the nif.
	vector<Rent> getVector() { return v; }//!< a function that returns the vector of rents.
};