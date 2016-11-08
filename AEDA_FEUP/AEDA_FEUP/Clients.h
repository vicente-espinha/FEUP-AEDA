#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Clients
{
public:
	Clients();
	//void makeReservation();

};

class Users : public Clients {

protected:
	string username, password;
	unsigned int points, nif;
	fstream f;
	vector<Users> usersVec;
public:
	Users(string username, string password, unsigned int nif, unsigned int points);
	string getUsername();
	string getPassword();
	unsigned int getPoints();
	unsigned int getNif();
	bool checkExistance(string username, string password);
};


