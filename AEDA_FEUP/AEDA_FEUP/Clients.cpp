#include "Clients.h"

Clients::Clients(){}

Users::Users(string username, string password, unsigned int nif, unsigned int points){

	this->username = username;
	this->password = password;
	this->nif = nif;

}

string Users::getUsername() { return username; }

string Users::getPassword() { return password; }

unsigned int Users::getPoints() { return points; }

unsigned int Users::getNif() { return nif; }




