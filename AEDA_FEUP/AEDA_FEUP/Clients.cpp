#include "Clients.h"

Clients::Clients(){}

Users::Users(string username, string password, long nif,  int points){
	this->username = username;
	this->password = password;
	this->nif = nif;
	this->points = points;
}

string Users::getUsername() { return username; }

string Users::getPassword() { return password; }

int Users::getPoints() { return points; }

long Users::getNif() { return nif; }




