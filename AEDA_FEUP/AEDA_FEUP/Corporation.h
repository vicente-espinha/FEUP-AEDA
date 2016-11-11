#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Clients.h"
#include "Utilities.h"

#include "Rent.h"
#include "Supplier.h"
#include "Reservations.h"
#include "Date.h"
#include "Rent.h"


using namespace std;

class Corporation
{
private:
	static Corporation* singleton_instance;
	string usersFile;
	string username, password;
	unsigned int nif;
	vector<Users> usersVec;

	vector<Supplier> suppliersVec;
	
public:
	static Corporation* instance();
	bool foundUsersFile(string userFiles);
	//void loadReservations();
	void loadUsers();
	void saveUsers();
	void registerUser();

	void loadSuppliers();
	void saveSuppliers();
	void registerSuppliers();
	//void makeReservation();
};

