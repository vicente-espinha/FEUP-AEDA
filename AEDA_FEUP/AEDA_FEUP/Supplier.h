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
public:	
	Supplier();
	Supplier(string n, string password, unsigned int ni, string ad);
	string getName() { return name; }//!< a function that returns the name.
	void setName(string s) { name = s; }//!< a function that sets the name.
	string getPassword() { return password; }//!< a function that returns the password.
	string getAddress() { return address; }//!< a function that returns the address.
	
	unsigned int getNif() { return nif; }//!< a function that returns the nif.

};