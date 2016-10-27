#pragma once
#include <iostream>
#include <string>

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
public:
	Users();
	void createClient();
	string * getUsername();
	unsigned int getPoints();
};


