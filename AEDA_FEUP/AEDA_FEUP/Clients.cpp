#include "Clients.h"

Clients::Clients(){}

Users::Users(string username, string password, long nif,  int points){

	this->username = username;
	this->password = password;
	this->nif = nif;
	this->points = points;

}

string Users::getUsername()const { return username; }

string Users::getPassword() { return password; }

int Users::getPoints() { return points; }

long Users::getNif() const{ return nif; }

bool operator==(const Users &u1,const Users &s2) {

	if (u1.nif == s2.nif && u1.password == s2.password && u1.points == s2.points && u1.username == s2.username)
		return true;
	else
		return false;
}


