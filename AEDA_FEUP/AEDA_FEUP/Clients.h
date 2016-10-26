#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Clients
{
public:
	Clients();
	virtual ~Clients();
	//void makeReservation();

};

class Users : public Clients {
	string username, password;
	unsigned int points, nif;
	fstream f;
public:
	Users(string username, string password, unsigned int nif, unsigned int points = 0);
	void createClient();
	string * getUsername();
	unsigned int getPoints();
	void addUser(string username, string password);
	bool checkExistance(string username, string password);
};


