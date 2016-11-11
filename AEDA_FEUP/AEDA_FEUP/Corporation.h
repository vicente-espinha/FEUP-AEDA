#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Clients.h"
#include "Utilities.h"
#include "Reservations.h"
#include "Date.h"

using namespace std;

/*template<typename T>*/
class Corporation
{
private:
	static Corporation* singleton_instance;
	string usersFile;
	string username, password;
	unsigned int nif;
	vector<Users> usersVec;
	//vector<Reservation<T>>reservationVec;
public:
	static Corporation* instance();
	bool foundUsersFile(string userFiles);
	//void loadReservations();
	void loadUsers();
	void saveUsers();
	void registerUser();
};

