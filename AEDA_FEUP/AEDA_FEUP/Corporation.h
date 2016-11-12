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
#include "Menu.h"


using namespace std;

class Corporation
{
private:
	static Corporation* singleton_instance;
	string usersFile, suppliersFile, reservationsFile;
	string username, supplierName;
	vector<Users> usersVec;
	//vector<Supplier> suppliersVec;
	//vector<Rent> rentsVec;
	//vector<Reservation> reservationsVec;
	
public:
	static Corporation* instance();

	bool foundUsersFile(string userFiles);
	void loadUsers();
	void saveUsers();
	void registerUser();

	bool foundSuppliersFile(string suppliersFile);
	void loadSuppliers();
	void saveSuppliers();
	void registerSupplier();

	bool foundReservationsFile(string reservationsFile);
	//void makeReservation();
	//void loadReservations();
	//void saveReservations();
};

